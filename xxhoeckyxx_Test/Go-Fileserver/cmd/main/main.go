package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func main() {
	mux := http.NewServeMux()

	fs := http.FileServer(http.Dir("./cmd/templates"))

	// Handler für die Startseite und statische Dateien
	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if r.URL.Path == "/" {
			http.ServeFile(w, r, "./cmd/templates/home.html")
			return
		}
		fs.ServeHTTP(w, r)
	})

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

// Handler für den Test-Endpunkt
func handleTest(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Test erfolgreich!, du bist nun startklar.")
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
	time.Sleep(3 * time.Second)
	fmt.Println(message)
	os.Exit(0)
}
