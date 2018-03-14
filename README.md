## Am Projekt teilnehmen

### Vorbereitung

  1. In GitHub einloggen / Einen GitHub Account erstellen. 
  1. Auswahl und Installation eins Git Clients (z.B. [Git Desktop](https://desktop.github.com/) oder [Git Kraken](https://www.gitkraken.com/))
  2. Auswahl einer IDE:
      - [Arduino IDE](https://www.arduino.cc/en/main/software) <- sehr einfach
      - [Eclipse für C/C++](https://www.eclipse.org/downloads/packages/) + Sloeber Plugin (in Eclipse>Help>Eclipse Marketplace> suchen nach Arduino oder Sloeber). Eclipse gibt es nur auf englisch und ist komplizierter vorzubereiten. Es besitzt aber dafür eine Autovervollständigung und weiter Komfortfunktionen.
  3. Klonen oder Forken dieses Repositories über den Git Client. Für Eclipse sollte es in einem Pfad ohne Leerzeichen befinden.  
  4. Projekt öffnen 
      1. <b>Arduino IDE:</b> Es kann einfach die .ino geöffnet und bearbeitet werden.   
      2. <b>Eclipse:</b> Nach dem Starten, dem Festlegen eines Workspaces und dem Installieren des Plugins, kann man unter "File>Import>General>Existing Projects into Workspace" den Pfad des Repositories angeben und das Projekt importieren.

### Ein einfacher Arbeitsablauf.

  Zu Beginn erstellt man mit 'git branch [name]' einen neuen Zweig mit dem namen [name] (natürlich ohne Klammern.)
  Evlt. geht es je nach Git Client auch einfacher. Nun stellt man sicher dass der Zweig ausgecheckt ist.
  Nachdem alles soweit vorbereitet ist kann man nun ganz normal mit dem Arbeiten beginnen. 
  Mit einem Git Commit kann man seinen Änderungen lokal eintragen und mit Git Push wird der Zweig mitsamt allen Änderungen in das Online Repository geladen.
  Wenn man nach evtl. sogar mehreren Sitzungen mit dem aktuellen Problem fertig ist, kann man eine Merge Request (Anfrage zum Zusammenlegen) stellen. Daraufhin wird der Versuch gestartet die Änderung in den Hautpfad(master) zu integrieren.
  
  Bei kleineren Änderungen kann man natürlich auch gleich auf dem master Zweig arbeiten.
  
  Mehr Informationen zum Arbeiten mit Git gibt es zum Beispiel [hier](https://rogerdudler.github.io/git-guide/index.de.html).
  
### Regeln zum Arbeiten

Geschriebener Code sollte kommentiert und ausreichend lesbar formatiert(Arduino IDE = strg+T, Eclipse = strg+umschlat+F) sein.
Größere Änderungen sollten auf einem extra Git-Zweig stattfinden und später gemerget werden.
Der Code muss immer von beiden IDE's kompilierbar sein. Dies sollte regelmäßig geprüft werden.

### Probleme/Issues

Falls Probleme auftreten oder Hilfe benötigt wird, kann man unter dem Tab ["Issues"](https://github.com/LitschiW/LimitedStepperMotor/issues) ein neues Issue mit Name, Beschreibung und Problemtyp (s. [Labels](https://github.com/LitschiW/LimitedStepperMotor/labels)) erstellt werden.

  
