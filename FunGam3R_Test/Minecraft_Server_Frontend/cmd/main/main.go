package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"os/exec"
	"os/signal"
	"syscall"
)

const (
	port        = ":8080"
	memorySize  = "1024M"
	serverJar   = "/opt/minecraft/minecraft_server.jar"
	templatesDir = "./cmd/templates/HTML"
)

func main() {
	mux := http.NewServeMux()

	fs := http.FileServer(http.Dir(templatesDir))

	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		handleRoot(w, r, fs)
	})
	mux.HandleFunc("/start", handleStartUp)
	mux.HandleFunc("/stop", handleClose)
	mux.HandleFunc("/test", handleTest)
	mux.HandleFunc("/upload", handleUpload)
	mux.HandleFunc("/download", handleDownload)
	mux.HandleFunc("/terminate", handleTerminate)

	fmt.Printf("Server listening on port %s\n", port)

	server := &http.Server{Addr: port, Handler: mux}

	go func() {
		err := server.ListenAndServe()
		if err != nil {
			log.Fatal(err)
		}
	}()

	waitForShutdown(server)
}

func handleRoot(w http.ResponseWriter, r *http.Request, fs http.Handler) {
	if r.URL.Path == "/" {
		http.ServeFile(w, r, "./cmd/templates/HTML/home.html")
		return
	}

	fs.ServeHTTP(w, r)
}

func handleStartUp(w http.ResponseWriter, r *http.Request) {
	pwd := exec.Command("pwd")
	cmd := exec.Command("java", "-Xms"+memorySize, "-Xmx"+memorySize, "-jar", serverJar, "nogui")
	cmd.Dir = "/opt/minecraft"

	pwdOutput, pwdErr := pwd.Output()
	if pwdErr != nil {
		errorMessage := fmt.Sprintf("Fehler beim Ausführen des 'pwd'-Befehls: %s", pwdErr)
		fmt.Fprintf(w, "%s\n", errorMessage)
		fmt.Println(errorMessage)
		return
	}

	fmt.Fprintf(w, "Aktuelles Verzeichnis: %s\n", pwdOutput)
	fmt.Println("Aktuelles Verzeichnis: " + string(pwdOutput))

	output, err := cmd.CombinedOutput()
	if err != nil {
		errorMessage := fmt.Sprintf("Fehler bei der Befehlsausführung: %s", err)
		fmt.Fprintf(w, "%s\n", errorMessage)
		fmt.Println(errorMessage)
		return
	}

	outputMessage := fmt.Sprintf("Befehl erfolgreich ausgeführt. Ausgabe:\n%s\n", output)
	fmt.Fprintf(w, "%s\n", outputMessage)
	fmt.Println(outputMessage)
}

func handleClose(w http.ResponseWriter, r *http.Request) {
	cmd := exec.Command("killall", "java")

	output, err := cmd.CombinedOutput()
	if err != nil {
		errorMessage := fmt.Sprintf("Fehler bei der Befehlsausführung: %s", err)
		fmt.Fprintf(w, "%s\n", errorMessage)
		fmt.Println(errorMessage)
		return
	}

	outputMessage := fmt.Sprintf("Befehl 'killall java' erfolgreich ausgeführt. Ausgabe:\n%s\n", output)
	fmt.Fprintf(w, "%s\n", outputMessage)
	fmt.Println(outputMessage)
}

func handleTest(w http.ResponseWriter, r *http.Request) {
	status, err := checkMinecraftServerStatus()
	if err != nil {
		testMessage := "Test erfolgreich, der Go-Server läuft, aber der Minecraft-Server ist nicht aktiv."
		fmt.Fprintf(w, "%s\n", testMessage)
		fmt.Println(testMessage)
		errorMessage := fmt.Sprintf("Fehler beim Überprüfen des Minecraft-Serverstatus: %s", err)
		fmt.Fprintf(w, "%s\n", errorMessage)
		fmt.Println(errorMessage)
	} else if status {
		testMessage := "Test erfolgreich, der Go-Server läuft und der Minecraft-Server ist aktiv."
		fmt.Fprintf(w, "%s\n", testMessage)
		fmt.Println(testMessage)
	}
}

func checkMinecraftServerStatus() (bool, error) {
	cmd := exec.Command("pgrep", "-f", "minecraft_server.jar")
	output, err := cmd.CombinedOutput()
	if err != nil {
		return false, err
	}

	return len(output) > 0, nil
}

func handleUpload(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Datei-Upload\n")
}

func handleDownload(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Datei-Download\n")
}

func handleTerminate(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Server wird heruntergefahren\n")
	shutdownServer()
	fmt.Fprintf(w, "Server erfolgreich heruntergefahren\n")
}

func waitForShutdown(server *http.Server) {
	stopChan := make(chan os.Signal, 1)
	signal.Notify(stopChan, os.Interrupt, syscall.SIGTERM)
	<-stopChan

	fmt.Println("\nServer wird heruntergefahren...")
	shutdownServer()
}

func shutdownServer() {
	var message = "Server erfolgreich heruntergefahren"
	fmt.Println(message)
	os.Exit(0)
}
