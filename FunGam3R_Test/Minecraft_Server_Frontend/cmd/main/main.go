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

func main() {
	mux := http.NewServeMux()

	fs := http.FileServer(http.Dir("./cmd/templates/HTML"))

	// Handler für die Startseite und statische Dateien
	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if r.URL.Path == "/" {
			http.ServeFile(w, r, "./cmd/templates/HTML/home.html")
			return
		}
		fs.ServeHTTP(w, r)
	})

	// Handler für den Start des Java-Befehls des Minecraft Servers
	mux.HandleFunc("/start", handleStartUp)

	// Handler für den Stop des Java-Minecraft Servers
	mux.HandleFunc("/stop", handleClose)

	// Handler für den Test-Endpunkt
	mux.HandleFunc("/test", handleTest)

	// Handler für den Upload-Endpunkt
	mux.HandleFunc("/upload", handleUpload)

	// Handler für den Download-Endpunkt
	mux.HandleFunc("/download", handleDownload)

	// Handler für den Terminate-Endpunkt
	mux.HandleFunc("/terminate", handleTerminate)

	port := ":8080"
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

// Handler für den Start des Java-Befehls des Minecraft Servers
func handleStartUp(w http.ResponseWriter, r *http.Request) {
	pwd := exec.Command("pwd")
	cmd := exec.Command("java", "-Xms1024M", "-Xmx1024M", "-jar", "/opt/minecraft/minecraft_server.jar", "nogui")
	cmd.Dir = "/opt/minecraft"

	pwdOutput, pwdErr := pwd.Output()
	if pwdErr != nil {
		errorMessage := fmt.Sprintf("Fehler beim Ausführen des 'pwd'-Befehls: %s", pwdErr)
		fmt.Fprintln(w, errorMessage)
		fmt.Println(errorMessage)
		return
	}
	fmt.Fprintf(w, "Aktuelles Verzeichnis: %s", pwdOutput)
	fmt.Println("Aktuelles Verzeichnis: " + string(pwdOutput))

	output, err := cmd.CombinedOutput()
	if err != nil {
		errorMessage := fmt.Sprintf("Fehler bei der Befehlsausführung: %s", err)
		fmt.Fprintln(w, errorMessage)
		fmt.Println(errorMessage)
		return
	}
	outputMessage := fmt.Sprintf("Befehl erfolgreich ausgeführt. Ausgabe:\n%s", output)
	fmt.Fprintln(w, outputMessage)
	fmt.Println(outputMessage)
}

// Handler für den Stop des Java-Minecraft-Servers
func handleClose(w http.ResponseWriter, r *http.Request) {
	cmd := exec.Command("killall", "java")

	output, err := cmd.CombinedOutput()
	if err != nil {
		errorMessage := fmt.Sprintf("Fehler bei der Befehlsausführung: %s", err)
		fmt.Fprintln(w, errorMessage)
		fmt.Println(errorMessage)
		return
	}
	outputMessage := fmt.Sprintf("Befehl 'killall java' erfolgreich ausgeführt. Ausgabe:\n%s", output)
	fmt.Fprintln(w, outputMessage)
	fmt.Println(outputMessage)
}

// Handler für den Test-Endpunkt
func handleTest(w http.ResponseWriter, r *http.Request) {
	testMessage := fmt.Sprintf("Test erfolgreich, der Go-Server läuft!")
	fmt.Fprintln(w, testMessage)
	fmt.Println(testMessage)
}

// Handler für den Upload-Endpunkt
func handleUpload(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Datei-Upload")
}

// Handler für den Download-Endpunkt
func handleDownload(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Datei-Download")
}

func handleTerminate(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Server wird heruntergefahren")
	shutdownServer()
	fmt.Fprintf(w, "Server erfolgreich heruntergefahren")
}

// Warten auf das Herunterfahren des Servers
func waitForShutdown(server *http.Server) {
	stopChan := make(chan os.Signal, 1)
	signal.Notify(stopChan, os.Interrupt, syscall.SIGTERM)
	<-stopChan

	fmt.Println("\nServer wird heruntergefahren...")
	shutdownServer()
}

// Herunterfahren des Servers
func shutdownServer() {
	var message = "Server erfolgreich heruntergefahren"
	fmt.Println(message)
	os.Exit(0)
}
