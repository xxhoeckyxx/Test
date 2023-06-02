var messages = [];

function addMessage(message) {
  var timestamp = new Date().toLocaleTimeString();
  var fullMessage = timestamp + ': ' + message;
  messages.push(fullMessage);
  if (messages.length > 6) {
    messages.shift();
  }
  displayMessages();
}

function displayMessages() {
  var output = document.getElementById('output');
  output.innerHTML = '';

  for (var i = 0; i < messages.length; i++) {
    output.innerHTML += '<p>' + messages[i] + '</p>';
  }
}

function testServer() {
  fetch('/test', { method: 'GET' })
    .then(function(response) {
      if (response.ok) {
        return response.text(); // Server-Antwort als Text zurückgeben
      } else {
        throw new Error('Error retrieving server response.');
      }
    })
    .then(function(responseText) {
      addMessage(responseText); // Server-Antwort zur Nachrichtenliste hinzufügen
    })
    .catch(function(error) {
      addMessage('An error occurred: ' + error);
    });
}

function terminateServer() {
  var timeoutDuration = 3000; // Timeout-Dauer in Millisekunden
  var isTerminated = false; // Flag, um den Server-Status zu verfolgen

  // Timeout-Funktion, die aufgerufen wird, wenn das Timeout abgelaufen ist
  var timeoutFunction = function() {
    if (!isTerminated) {
      addMessage('Erfolgreich heruntergefahren!');
    }
  };

  // Starten des Timeout-Timers
  var timeoutTimer = setTimeout(timeoutFunction, timeoutDuration);

  fetch('/terminate', { method: 'GET' })
    .then(function(response) {
      clearTimeout(timeoutTimer); // Timeout-Timer löschen, da eine Antwort erhalten wurde
      if (response.ok) {
        return response.text(); // Server-Antwort als Text zurückgeben
      } else {
        throw new Error('Error terminating server.');
      }
    })
    .then(function(responseText) {
      addMessage(responseText); // Server-Antwort zur Nachrichtenliste hinzufügen
      isTerminated = true; // Server wurde erfolgreich heruntergefahren
    })
    .catch(function(error) {
      addMessage('An error occurred: ' + error);
      isTerminated = true; // Server wurde mit einem Fehler heruntergefahren
    });
}


function cautionTerminateServer() {
  alert("Wenn dieser Server über den Button ausgeschalten wird, kann er nur Vorort eingeschalten werden!");
}

setInterval(function() {
  displayMessages();
}, 1000);