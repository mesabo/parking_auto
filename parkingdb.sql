-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : ven. 09 avr. 2021 à 19:50
-- Version du serveur :  8.0.23
-- Version de PHP : 8.0.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `parkingdb`
--

-- --------------------------------------------------------

--
-- Structure de la table `autos`
--

CREATE TABLE `autos` (
  `id` int NOT NULL,
  `immat` varchar(255) DEFAULT NULL,
  `entree` datetime DEFAULT NULL,
  `sortie` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `autos`
--

INSERT INTO `autos` (`id`, `immat`, `entree`, `sortie`) VALUES
(2, '6132JE01', '2021-04-08 12:35:50', '2021-04-08 12:52:11'),
(3, '6132JE01', '2021-04-08 12:41:56', '2021-04-09 18:53:31'),
(4, '0102AB02', '2021-04-08 13:24:54', '2021-04-09 19:11:19'),
(5, '1234ab01', '2021-04-09 17:23:14', NULL),
(6, '1234AB01', '2021-04-09 17:24:23', '2021-04-09 18:59:54'),
(7, '0101ab01', '2021-04-09 19:01:00', NULL),
(9, '1234AB01', '2021-04-09 19:09:46', '2021-04-09 19:13:58'),
(10, '1234AB01', '2021-04-09 19:19:36', '2021-04-09 19:39:24'),
(11, '1234AB02', '2021-04-09 19:20:19', NULL),
(12, '12345678', '2021-04-09 19:25:07', '2021-04-09 19:28:34');

-- --------------------------------------------------------

--
-- Structure de la table `factures`
--

CREATE TABLE `factures` (
  `id` int NOT NULL,
  `place` int DEFAULT NULL,
  `auto` int DEFAULT NULL,
  `montant` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `factures`
--

INSERT INTO `factures` (`id`, `place`, `auto`, `montant`) VALUES
(1, 4, 4, '0'),
(2, 4, 3, '60000'),
(3, 3, 3, '300000'),
(7, 1, 6, NULL),
(10, 6, 9, '2850000'),
(11, 6, 10, '2500'),
(12, 9, 11, NULL),
(13, 8, 12, '0');

-- --------------------------------------------------------

--
-- Structure de la table `places`
--

CREATE TABLE `places` (
  `id` int NOT NULL,
  `code` varchar(255) DEFAULT NULL,
  `type` varchar(255) DEFAULT NULL,
  `etat` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `places`
--

INSERT INTO `places` (`id`, `code`, `type`, `etat`) VALUES
(1, 'PL21A', 'VOITURES', 0),
(2, 'PL21B', 'VOITURES', 1),
(3, 'PL21C', 'VOITURES', 0),
(4, 'PL21D', 'VOITURES', 0),
(5, 'PL21E', 'VOITURES', 0),
(6, 'PL21F', 'CAMIONS', 1),
(7, 'PL21G', 'CAMIONS', 0),
(8, 'PL21H', 'CAMIONS', 0),
(9, 'PL21I', 'CAMIONS', 0),
(10, 'PL21J', 'CAMIONS', 0),
(11, 'PL21K', 'DEUX_ROUES', 0),
(12, 'PL21L', 'DEUX_ROUES', 0),
(13, 'PL21M', 'DEUX_ROUES', 0),
(14, 'PL21N', 'DEUX_ROUES', 0),
(15, 'PL21O', 'DEUX_ROUES', 0);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `autos`
--
ALTER TABLE `autos`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `factures`
--
ALTER TABLE `factures`
  ADD PRIMARY KEY (`id`),
  ADD KEY `place` (`place`),
  ADD KEY `auto` (`auto`);

--
-- Index pour la table `places`
--
ALTER TABLE `places`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `autos`
--
ALTER TABLE `autos`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT pour la table `factures`
--
ALTER TABLE `factures`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `factures`
--
ALTER TABLE `factures`
  ADD CONSTRAINT `factures_ibfk_1` FOREIGN KEY (`place`) REFERENCES `places` (`id`),
  ADD CONSTRAINT `factures_ibfk_2` FOREIGN KEY (`auto`) REFERENCES `autos` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
