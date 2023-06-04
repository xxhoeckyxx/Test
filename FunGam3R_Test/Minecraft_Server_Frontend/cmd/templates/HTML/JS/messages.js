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
