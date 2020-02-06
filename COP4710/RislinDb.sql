
 DROP SCHEMA IF EXISTS `mydb` ;  
CREATE SCHEMA IF NOT EXISTS `RislinDb`;  
USE `RislinDb`;
 



CREATE  TABLE IF NOT EXISTS `Property` (
  `address` CHAR(50) NOT NULL ,
  `ownerName` CHAR(30) NOT NULL ,
  `price` INT NOT NULL ,
  PRIMARY KEY (`address`) );




CREATE  TABLE IF NOT EXISTS `House` (
  `bedrooms` INT NOT NULL ,
  `bathrooms` INT NOT NULL ,
  `size` INT NOT NULL ,
  `address` CHAR(50) NOT NULL);




CREATE  TABLE IF NOT EXISTS `BusinessProperty` (
  `type` CHAR(20) NOT NULL ,
  `size` INT NOT NULL ,
  `address` CHAR(50) NOT NULL);



CREATE  TABLE IF NOT EXISTS `Firm` (
  `id` INT NOT NULL ,
  `name` CHAR(30) NOT NULL ,
  `address` CHAR(50) NOT NULL ,
  PRIMARY KEY (`id`) );




CREATE  TABLE IF NOT EXISTS `Agent` (
  `id` INT NOT NULL ,
  `name` CHAR(30) NOT NULL ,
  `phone` CHAR(12) NOT NULL ,
  `firmid` INT NOT NULL ,
  `dateStarted` CHAR(12) NOT NULL ,
  PRIMARY KEY (`id`, `firmid`) );




CREATE  TABLE IF NOT EXISTS `Buyer` (
  `id` INT NOT NULL ,
  `name` CHAR(30) NULL ,
  `phone` CHAR(12) NULL ,
  `propertyType` CHAR(20) NULL ,
  `bedrooms` INT NULL ,
  `bathrooms` INT NULL ,
  `businessPropertyType` CHAR(20),
  `maximumPreferredPrice` INT NULL ,
  `minimumPreferredPrice` INT NULL ,
  PRIMARY KEY (`id`) );




CREATE  TABLE IF NOT EXISTS `Listings` (
  `address` CHAR(50) NOT NULL ,
  `agentid` INT NULL ,
  `mlsNumber` INT NOT NULL ,
  `dateListed` CHAR(12) NOT NULL ,
  PRIMARY KEY (`address`, `mlsNumber`) );




CREATE  TABLE IF NOT EXISTS `WorksWith` (
  `buyerid` INT NOT NULL ,
  `agentid` INT NOT NULL ,
  PRIMARY KEY (`buyerid`, `agentid`) );






INSERT INTO `Property` (`address`, `ownerName`, `price`) VALUES 
('123 Fake st', 'Luke Carol', 200000),
 ('222 Not Real ln', 'Mariah Hewitt', 150000),
 ('54 Huey ct', 'Tony Yung', 100000),
 ('19 Anvulle rd', 'Peter Jones', 250000),
 ('22 Orange dr', 'Lois Greene', 300000),
 ('13 SW st', 'Diego Chavez', 120000),
('22 Long blvd', 'Parker Ray', 100000),
 ('59 Giant rd', 'Marty Upton', 800000),
 ('99 Moon Walk st', 'Zoey Riley', 140000),
 ('52 Gary rd', 'Sarah Rice', 80000);





INSERT INTO `House` (`bedrooms`, `bathrooms`, `size`, `address`) VALUES (3, 3, 2000, '123 Fake st'),
(3, 2, 1400, '222 Not Real ln'),
(2, 2, 1200, '54 Huey ct'),
 (4, 3, 2400, '19 Anvulle rd'),
 (4, 2, 2800, '22 Orange dr');





INSERT INTO `BusinessProperty` (`type`, `size`, `address`) VALUES ('Office Space', 1200, '13 SW st'),
 ('Gas Station', 800, '22 Long blvd'),
 ('Store Front', 1400, '59 Giant rd'),
 ('Gas Station', 1000, '99 Moon Walk st'),
 ('Office Space', 1300, '52 Gary rd');





INSERT INTO `Firm` (`id`, `name`, `address`) VALUES 
(2210, 'House Corp', '45 Barker rd'),
 (1023, 'We Sell Homes', '15 Hope st'),
 (5589, 'Blue Realty', '25 Blue ct'),
 (2569, 'Joes Realty', '16 Patriot ave'),
 (4785, 'New Home inc', '22 Badger st');





INSERT INTO `Agent` (`id`, `name`, `phone`, `firmid`, `dateStarted`) VALUES (100, 'Miller Saint', '405-999-8574', 2210, '1/1/2001'),
 (101, 'Mark Colby', '205-222-3456', 1023, '1/2/2000'),
 (102, 'Dave Frank', '345-670-1258', 5589, '2/3/2004'),
 (103, 'Ruby Cross', '456-781-0254', 2569, '3/22/2002'),
(104, 'Sam Risen', '567-898-7926', 4785, '9/18/2000'),
(105, 'Casey Veggie', '319-068-0221', 0383, '06/28/2000');






INSERT INTO `Buyer` (`id`, `name`, `phone`, `propertyType`, `bedrooms`, `bathrooms`, `businessPropertyType`, `minimumPreferredPrice`, `maximumPreferredPrice`) VALUES (3696, 'Clark King', '585-147-4455', 'house', 3, 2, NULL, 100000, 200000),
 (2585, 'Lois Long', '696-878-4455', 'business', NULL, NULL, 'Gas Station', 50000, 120000),
 (1474, 'Mike Bole', '369-852-7447', 'house', 4, 2, NULL, 200000, 300000),
 (7414, 'Tony Cane', '989-565-4441', 'business', NULL, NULL, 'Office Space', 80000, 120000),
 (8525, 'Jane Billow', '850-222-6666', 'house', 2, 2, NULL, 100000, 150000),
 (9933, 'Tyler Tock', '407-508-0664', 'business', NULL, NULL, 'Store Front', 100000, 200000);





INSERT INTO `Listings` (`address`, `agentid`, `mlsNumber`, `dateListed`) VALUES ('123 Fake st', 101, 54532, '02/15/2006'),
 ('222 Not Real ln', 102, 35126, '02/23/2006'),
 ('54 Huey ct', 103, 22536, '02/19/2006'),
 ('19 Anvulle rd', 104, 52532, '02/2/2006'),
 ('22 Orange dr', 105, 11244, '02/25/2006'),
 ('13 SW st', 101, 56542, '01/24/2006'),
 ('22 Long blvd', 102, 65355, '03/8/2006'),
 ('59 Giant rd', 103, 68244, '01/18/2006'),
 ('99 Moon Walk st', 104, 65321, '02/23/2006'),
 ('52 Gary rd', 105, 54211, '04/15/2006');





INSERT INTO `WorksWith` (`buyerid`, `agentid`) VALUES      (3696,100),
 (2585, 101),
 (1474, 102),
 (7414, 103),
 (8525, 104),
 (9933, 105),
 (3696,101),
 (1474,101),
 (7414,101),
 (8525,101),
 (9933,101);




