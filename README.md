# Sockets README

## Language Selection

- [German](#deutsch)
- [English](#english)

## English

Sockets in computer programming allow computers to communicate with each other over networks, similar to phone conversations between people.

## Similarity to Phones

- **IP Address and Port:** Each computer has an IP address in the network. The port is like an application number on the phone.

## Types of Sockets

- **Stream Sockets (TCP):** Similar to a phone call, words arrive in order. Information security is ensured.
- **Datagram Sockets (UDP):** Similar to sending postcards. Messages can arrive in any order, errors are possible.

## Server and Client

- **Server:** Waits for calls, like a receptionist. Directs calls.
- **Client:** Makes calls to obtain information.

## Connection Establishment

- **TCP:** Connection in three steps: "Hello" - "Hello, I'm listening" - "Okay, we can talk".
- **UDP:** No formal connection setup, messages are sent without prior negotiation.

## Socket Actions

- **bind:** Connects IP address and port to socket.
- **listen:** Puts socket in wait mode for calls.
- **accept:** Accepts calls, opens connection.
- **connect:** Establishes connection.
- **send:** Sends information.
- **recv:** Receives information.

## The `newSocket` Variable in Server Code

The `newSocket` variable in the server code represents a new socket that is created to handle communication with a specific client. Its role in the context of the server-client communication process is explained as follows:

1. **Server Socket (`serverSocket`):** This socket is created using the `socket()` function and is used for listening for incoming client connections. It remains open throughout the server's lifetime and is responsible for accepting new client connections.

2. **Client Socket (`newSocket`):** When a client connects to the server, the `accept()` function is used to create a new socket, referred to as the `newSocket`, to handle communication with that specific client. This new socket is unique to each client connection and is used to send and receive data between the server and that particular client.

Think of the `serverSocket` as the reception desk of a hotel, where guests (clients) come in and get assigned their own room (the `newSocket`) for private conversations (data exchange) with the receptionist (server).

Here's how the process works:

1. The server creates a listening socket (`serverSocket`) and starts listening for incoming connections.
2. When a client connects, the server uses `accept()` to create a new socket (`newSocket`) dedicated to that client.
3. The server and client can then exchange data through their respective sockets (`newSocket` on the server side and a similar socket on the client side).
4. After the communication is done or the client disconnects, the server closes the `newSocket`.

This mechanism allows the server to handle multiple clients simultaneously by creating separate `newSocket` instances for each client, ensuring that each client's communication remains isolated.

---



## Deutsch

Sockets in der Computer-Programmierung ermöglichen Computern, über Netzwerke miteinander zu kommunizieren, ähnlich wie Telefonate zwischen Menschen.


## Deutsch

Sockets in der Computer-Programmierung ermöglichen Computern, über Netzwerke miteinander zu kommunizieren, ähnlich wie Telefonate zwischen Menschen.

## Ähnlichkeit zu Telefonen

- **IP-Adresse und Port:** Jeder Computer hat eine IP-Adresse im Netzwerk. Der Port ist wie eine Anwendungsnummer am Telefon.

## Arten von Sockets

- **Stream-Sockets (TCP):** Ähnlich einem Telefonanruf, Worte kommen in Reihenfolge an. Informationssicherheit ist gewährleistet.
- **Datagramm-Sockets (UDP):** Ähnlich dem Versand von Postkarten. Nachrichten können in beliebiger Reihenfolge ankommen, Fehler sind möglich.

## Server und Client

- **Server:** Wartet auf Anrufe, wie eine Rezeptionistin. Leitet Anrufe weiter.
- **Client:** Tätigt Anrufe, um Informationen zu erhalten.

## Verbindungsaufbau

- **TCP:** Verbindung in drei Schritten: "Hallo" - "Hallo, ich höre zu" - "Ok, wir können sprechen".
- **UDP:** Kein formeller Verbindungsaufbau, Nachrichten werden ohne Vorverhandlung gesendet.

## Socket-Aktionen

- **bind:** Verbindet IP-Adresse und Port mit Socket.
- **listen:** Setzt Socket in Wartemodus für Anrufe.
- **accept:** Nimmt Anrufe an, öffnet Verbindung.
- **connect:** Baut Verbindung auf.
- **send:** Sendet Informationen.
- **recv:** Empfängt Informationen.

## Die `newSocket` Variable im Servercode

Die `newSocket`-Variable im Servercode repräsentiert einen neuen Socket, der erstellt wird, um die Kommunikation mit einem bestimmten Client zu handhaben. Ihre Rolle im Kontext des Server-Client-Kommunikationsprozesses wird folgendermaßen erklärt:

1. **Server-Socket (`serverSocket`):** Dieser Socket wird mithilfe der `socket()`-Funktion erstellt und dient zum Lauschen auf eingehende Client-Verbindungen. Er bleibt während der gesamten Lebensdauer des Servers geöffnet und ist dafür verantwortlich, neue Client-Verbindungen anzunehmen.

2. **Client-Socket (`newSocket`):** Wenn sich ein Client mit dem Server verbindet, wird die `accept()`-Funktion verwendet, um einen neuen Socket namens `newSocket` zu erstellen, der die Kommunikation mit diesem speziellen Client behandelt. Dieser neue Socket ist eindeutig für jede Client-Verbindung und wird verwendet, um Daten zwischen dem Server und diesem bestimmten Client zu senden und zu empfangen.

Denken Sie an `serverSocket` wie an den Empfangstresen eines Hotels, an dem Gäste (Clients) eintreten und ihr eigenes Zimmer (den `newSocket`) für private Gespräche (Datenübertragung) mit dem Empfangschef (Server) zugewiesen bekommen.

So funktioniert der Prozess:

1. Der Server erstellt einen lauschenden Socket (`serverSocket`) und beginnt mit dem Lauschen auf eingehende Verbindungen.
2. Wenn ein Client sich verbindet, verwendet der Server `accept()`, um einen neuen Socket (`newSocket`) zu erstellen, der diesem Client gewidmet ist.
3. Der Server und der Client können dann Daten über ihre jeweiligen Sockets austauschen (`newSocket` auf der Serverseite und ein ähnlicher Socket auf der Clientseite).
4. Nachdem die Kommunikation abgeschlossen ist oder der Client die Verbindung trennt, schließt der Server den `newSocket`.

Dieser Mechanismus ermöglicht es dem Server, mehrere Clients gleichzeitig zu behandeln, indem separate `newSocket`-Instanzen für jeden Client erstellt werden, um sicherzustellen, dass die Kommunikation jedes Clients isoliert bleibt.
