package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
)


var messages []string // Deklaration der Variable messages

func addErrorMessage(message string) {
	messages = append(messages, message)
	if len(messages) > 6 {
		messages = messages[1:]
	}
}

func SetupServer(shutdown chan bool, server *http.Server, mux *http.ServeMux) {
	fs := http.FileServer(http.Dir("./templates"))

	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if r.URL.Path == "/" {
			http.ServeFile(w, r, "./templates/main.html")
			return
		}
		fs.ServeHTTP(w, r)
	})

	mux.HandleFunc("/Viedos", handleUploadManifest)

	mux.HandleFunc("/Bilder", handleUploadWASM)

	mux.HandleFunc("/test", func(w http.ResponseWriter, r *http.Request) {
		res, err := http.Get("http://backend:9998/")
		if err != nil {
			fmt.Fprintf(w, "failed to contact backend. Error code: %s", err)
		} else {
			body, _ := io.ReadAll(res.Body)
			fmt.Fprintf(w, "Test successful!\n Current Status: %s", body)
		}
	})

	mux.HandleFunc("/terminate", func(w http.ResponseWriter, r *http.Request) {
		fmt.Println("I was asked to Terminate")
		fmt.Fprint(w, "shutting down...")
		shutdown <- true
	})

	fmt.Println("+++ server starting +++")
	err := server.ListenAndServe()
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	mux := http.NewServeMux()
	server := &http.Server{Addr: ":8080", Handler: mux}
	shutdown := make(chan bool, 1)
	go SetupServer(shutdown, server, mux)

	fmt.Println("+++ waiting for shutdown signal +++")
	<-shutdown
	server.Shutdown(context.Background())
}
