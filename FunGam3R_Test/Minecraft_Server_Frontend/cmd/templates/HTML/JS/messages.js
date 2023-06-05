var messages = [];

function addMessage(message) {
  var timestamp = new Date().toLocaleTimeString();
  var fullMessage = timestamp + ': ' + message.trim("\n"); // Leerzeichen und "New Line" am Anfang und Ende der Nachricht entfernen
  if (fullMessage.length > 0) { // Prüfen, ob die Nachricht nicht leer ist
    messages.push(fullMessage);
    if (messages.length > 6) {
      messages.shift();
    }
    displayMessages();
  }
}

function displayMessages() {
  var output = document.getElementById('output');
  output.innerHTML = messages.join('<br>');
}

setInterval(function () {
  displayMessages();
}, 1500);
