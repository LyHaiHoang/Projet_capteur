# Projet : Capteur Graphite à Crayon

## Table des matières
- [Contexte](#contexte)
- [Réalisation du projet](#réalisation-du-projet)
  - [1. Matériaux utilisés](#1-matériaux-utilisés)
  - [2. Simulation électronique en utilisant LTSpice](#2-simulation-électronique-en-utilisant-ltspice)
  - [3. Conception du circuit PCB en utilisant KiCad](#3-conception-du-circuit-pcb-en-utilisant-kicad)
    - [3.1 Réalisation du symbole des composants](#31-réalisation-du-symbole-des-composants)
    - [3.2 Réalisation du schéma électronique](#32-réalisation-du-schéma-électronique)
    - [3.3 Réalisation des empreintes des composants](#33-réalisation-des-empreintes-des-composants)
    - [3.4 Réalisation du PCB](#34-réalisation-du-pcb)
  - [4. Code Arduino](#4-code-arduino)
  - [5. Application Android via MIT App Inventor](#5-application-android-via-mit-app-inventor)
  - [6. Réalisation du Shield](#6-réalisation-du-shield)
  - [7. Banc de test](#7-banc-de-test)
  - [8. Datasheet](#8-datasheet)
- [Conclusion](#conclusion)
- [Références](#références)
- [Contact](#contact)

---

## Contexte
Ce projet vise à développer un capteur basé sur le graphite de crayon pour des applications en instrumentation. L'objectif est d'explorer les propriétés conductrices du graphite et de les exploiter dans un circuit électronique interactif, connecté à une application mobile via Bluetooth.

---

## Réalisation du projet

### 1. Matériaux utilisés
Les composants utilisés proviennent principalement de la salle d'instrumentation. Voici la liste complète :
- 1 carte Arduino UNO
- 1 module Bluetooth HC-05
- 1 encodeur rotatif
- 1 écran OLED
- 1 capteur de flexion commercial
- 1 capteur graphite à crayon
- 1 amplificateur de transimpédance LTC1050
- 1 potentiomètre numérique
- 2 supports IC
- Résistances : 1 × 1kΩ, 1 × 10kΩ, 2 × 100kΩ
- Condensateurs : 3 × 100nF, 1 × 1µF

---

### 2. Simulation électronique en utilisant LTSpice
Les différents sous-circuits ont été simulés pour valider leur comportement théorique avant implémentation sur le breadboard. En particulier, l’amplificateur de transimpédance a été testé pour évaluer le gain et la réponse aux variations de courant.

---

### 3. Conception du circuit PCB en utilisant KiCad

#### 3.1 Réalisation du symbole des composants
Les composants non présents dans les bibliothèques standards de KiCad (module Bluetooth, encodeur, capteur de flexion, etc.) ont été créés manuellement.

#### 3.2 Réalisation du schéma électronique
Le schéma électronique a été conçu en intégrant tous les composants et en optimisant les connexions pour réduire les interférences et pertes.

#### 3.3 Réalisation des empreintes des composants
Les empreintes physiques (footprints) des composants ont été créées pour permettre un placement précis sur le PCB.

#### 3.4 Réalisation du PCB
Le circuit imprimé a été dessiné avec une attention particulière portée à la disposition des pistes pour minimiser les couplages parasites et faciliter le routage manuel.

---

### 4. Code Arduino
Le code Arduino permet de lire les valeurs du capteur graphite, de gérer l'affichage OLED, la communication Bluetooth et le contrôle via l'encodeur rotatif.

---

### 5. Application Android via MIT App Inventor
Une application mobile a été développée pour :
- Recevoir les données en Bluetooth,
- Afficher les mesures en temps réel,
- Interagir avec le capteur de manière intuitive.

---

### 6. Réalisation du Shield
Un shield personnalisé a été conçu pour s’adapter à l’Arduino UNO, permettant un branchement propre et sécurisé de tous les composants.

---

### 7. Banc de test
Afin de valider le fonctionnement du système, plusieurs tests ont été réalisés :
- Vérification des connexions,
- Mesure des signaux et tensions aux points clés,
- Test de communication Bluetooth.

Les tests ont permis d’identifier et de corriger certains dysfonctionnements avant la fabrication du PCB final.

---

### 8. Datasheet
Les fiches techniques des principaux composants (LTC1050, HC-05, écran OLED, etc.) sont disponibles dans le dossier `datasheet/` du projet.

---

## Conclusion
Ce projet démontre la faisabilité d’un capteur à base de graphite de crayon pour des applications d’instrumentation. Le prototype final est capable de détecter des variations de résistance liées à la pression exercée sur le graphite. Des perspectives d’amélioration incluent l’intégration d’un microcontrôleur plus performant, une alimentation autonome, et un PCB plus compact.

---

## Références
- Fiches techniques des composants (LTC1050, HC-05, etc.)
- Documentation Arduino
- Tutoriels MIT App Inventor
- Outils de simulation LTSpice et KiCad

---

## Contact

### Étudiants
- **Yoann Lai Koun Sing** : laikouns@insa-toulouse.fr  
- **Viet Hoang Pham** : vpham@insa-toulouse.fr  
- **Ly Hai Hoang** : lhoang@insa-toulouse.fr  

### Enseignants
- **Jérémie Grisolia** : jeremie.grisolia@insa-toulouse.fr
