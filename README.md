# Sockets README

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

Sockets sind Grundlage für Netzwerk-Programmierung, genutzt für Webseiten, E-Mails, Datei-Übertragungen und Spiele. APIs ermöglichen Socket-Nutzung und Kommunikation in Programmen.

