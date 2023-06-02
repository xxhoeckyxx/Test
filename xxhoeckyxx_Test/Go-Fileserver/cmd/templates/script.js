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
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/test', true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (xhr.status === 200) {
                var response = xhr.responseText;
                addMessage(response);
            } else {
                addMessage('Error retrieving server response.');
            }
        }
    };
    xhr.send();
}

function terminateServer() {
    fetch('/terminate', { method: 'POST' })
        .then(function(response) {
            if (response.ok) {
                return response.text(); // Server-Antwort als Text zurückgeben
            } else {
                throw new Error('Error terminating server.');
            }
        })
        .then(function(responseText) {
            addMessage(responseText); // Server-Antwort zur Nachrichtenliste hinzufügen
        })
        .catch(function(error) {
            addMessage('An error occurred: ' + error);
        });
}

function cautionServer() {
    addMessage("If you turn off the server via this button, you can no longer start it via this page!");
}

setInterval(function() {
    displayMessages();
}, 1000);
