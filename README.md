# Projet Capteur Graphite à Crayon

# Table des matières
• [Contexte](#Contexte)
• [1. Matériaux utilisés](#1.-Matériaux-utilisés)
• [2. Simulation électronique en utilisant LTSpice](#2.-Simulation-électronique-en-utilisant-LTSpice)
• [3. Conception du circuit PCB en utilisant KiCad](#3.-Conception-du-circuit-PCB-en-utilisant-KiCad)
   • [Réalisation du symbole des composants](#Réalisation-du-symbole-des-composants)
   • [Réalisation du schéma électronique](#Réalisation-du-schéma-électronique)
   • [Réalisation des empreintes des composants](#Réalisation-des-empreintes-des-composants)
   • [Réalisation du PCB](#Réalisation-du-PCB)
• [4. Code Arduino](#4.-Code Arduino)
• [5. Application Android APK via MIT App Inventor](#5.-Applicatio-Android-APK-via-MIT-App-Inventor)
• [6. Réalisation du Shield](#6.-Réalisation-du-Shield)
• [7. Banc de test](#7.-Banc-de-test)
• [8. Datasheet](#8.-Datasheet)
• [Conclusion](#Conclusion)
• [Références](#Références)
• [Contacts](#Contacts)





# Contexte
Ce projet vise à développer un capteur de flexion en graphite. Ce capteur est basé sur du graphite de crayon pour des applications en instrumentation. L'objectif est e piloter un ensemble de module arduino, d'explorer les propriétés conductrices du graphite et de les exploiter dans un circuit électronique interactif.


# Réalisation du projet

   ### 1. Matériaux utilisés

Dans ce projet, nous utilisons des composants électroniques et des modules disponibles dans la salle d'instrumentation avec une carte Arduino UNO. Tous les composants sont listés ci-dessous :
   * 1 carte Arduino UNO
   * 1 module Bluetooth HC-05
   * 1 encodeur rotatif
   * 1 écran OLED
   * 1 capteur de flexion commercial
   * 1 capteur graphite à crayon
   * 1 amplificateur de transimpédance LTC1050
   * 1 potentiomètre numérique
   * 2 supports IC
   * 1 résistance 1kΩ, 1 résistance 10kΩ, 2 résistances 100kΩ
   * 3 condensateurs 100nF, 1 condensateur 1µF


### 2. Simulation électronique en utilisant LTSpice
![Schéma 1](README_Image/)

Ce circuit électronique a pour objetif de filtrer le signal du capteur de graphite et de l'ampllifier afin d'obtenir des valeurs de meilleures valeurs de résistance. Dans un premier temps, il a été modélisé et testé sur LTSpice afin d'étudier sa réponse en sortie en focntion de la fréquence du signal d'entrée. L'influence de la valeur de la résistance R2.

Dans la suite du projet, il est supposé que le signal délivré par le capteur de graphite est de fréquence basse. En effet, la carte arduino délivre un courant continu (~50Hz).


### 3. Conception du circuit PCB en utilisant KiCad
![Schéma 2](README_Image/)

Afin de concevoir le circuit électronique sur lequel sera branché l'ensemble des modules arduino, le logiciel KiCad a été utilisé.
L'impression du circuit s'est ensuite faite par méthode chimie:
   * Plaque de cuivre/résine dont la face en cuivre est enduite d'une résine photosensible;
   * Insolation de la résine sur les parties du cuivre non voulue;
   * Attaque chimique dans un bain révélateur;
   * Rinçage du circuit;


#### Réalisation du symbole des composants:
Pour commencer notre circuit de PCB, il est nécessaire de créer les symboles des composants qui ne sont pas disponibles dans la bibliothèque de KiCad. Nous réalisons les symboles du module Bluetooth, de l'encodeur rotatif, du capteur de flexion, etc., afin de les ajouter au schéma de connexion entre les composants et la carte Arduino UNO.

#### Réalisation du schéma électronique:
Nous avons conçu le schéma électronique en utilisant KiCad, en intégrant les composants nécessaires et en optimisant les connexions pour minimiser les interférences et les pertes de signal.

#### Réalisation des empreintes des composants:

#### Réalisation du PCB :

### 4. Code Arduino

### 5. Application Android APK via MIT App Inventor

### 6. Réalisation du Shield

### 7. Banc de test
Afin de valider le bon fonctionnement du circuit, plusieurs tests ont été effectués :
- Vérification de la connectivité des composants.
- Mesure des signaux et des tensions aux différents points clés du circuit.
- Tests de communication entre le capteur et le module Bluetooth HC-05.
Ces tests nous ont permis d’identifier et de corriger certains dysfonctionnements avant la fabrication du PCB final.

### 8. Datasheet

## Conclusion
Le projet a permis de démontrer la faisabilité d'un capteur à base de graphite pour des applications en instrumentation. Nous avons réussi à concevoir un circuit fonctionnel et à développer un prototype capable de mesurer des variations de résistance du graphite en fonction de la pression exercée. Des améliorations futures pourraient inclure l'intégration d'un microcontrôleur plus avancé et l'optimisation du design du PCB pour une meilleure stabilité.

## Références

## Contacts

### Étudiants :
* Yoann Lai Koun Sing : laikouns@insa-toulouse.fr
* Viet Hoang Pham : vpham@insa-toulouse.fr
* Ly Hai Hoang : lhoang@insa-toulouse.fr

### Enseignants :
* Jérémie Grisolia : jeremie.grisolia@insa-toulouse.fr
