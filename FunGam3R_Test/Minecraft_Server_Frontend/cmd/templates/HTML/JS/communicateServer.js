function sendRequest(endpoint) {
    fetch(endpoint, { method: 'GET' })
        .then(function (response) {
            if (response.ok) {
                return response.text(); // Server-Antwort als Text zurückgeben
            } else {
                throw new Error('Error retrieving server response.');
            }
        })
        .then(function (responseText) {
            var responses = responseText.split('\n'); // Server-Antworten auf Zeilenumbrüche aufteilen
            for (var i = 0; i < responses.length; i++) {
                var trimmedResponse = responses[i].trim(); // Leerzeichen am Anfang und Ende der Antwort entfernen
                if (trimmedResponse.length > 0) { // Prüfen, ob die Antwort nicht leer ist
                    addMessage(trimmedResponse); // Server-Antworten einzeln zur Nachrichtenliste hinzufügen
                }
            }
        })
        .catch(function (error) {
            addMessage('An error occurred: ' + error);
        });
}
