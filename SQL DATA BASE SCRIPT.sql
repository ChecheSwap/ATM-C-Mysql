
SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

CREATE TABLE IF NOT EXISTS `mydb`.`usuario` (
  `idusuario` INT NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(45) NOT NULL,
  `saldo` DOUBLE NOT NULL,
  `fechanacimiento` VARCHAR(25) NOT NULL,
  `curp` VARCHAR(30) NOT NULL,
  `rfc` VARCHAR(30) NOT NULL,
  `calle` VARCHAR(40) NOT NULL,
  `colonia` VARCHAR(50) NOT NULL,
  `cp` VARCHAR(10) NOT NULL,
  `nacionalidad` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idusuario`))
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `mydb`.`depositos` (
  `iddeposito` INT NOT NULL AUTO_INCREMENT,
  `saldoinicial` DOUBLE NOT NULL,
  `saldofinal` DOUBLE NOT NULL,
  `monto` DOUBLE NOT NULL,
  `fecha` VARCHAR(20) NOT NULL,
  `idusuario` INT NOT NULL,
  PRIMARY KEY (`iddeposito`),
  INDEX `fk_depositos_usuario_idx` (`idusuario` ASC),
  CONSTRAINT `fk_depositos_usuario`
    FOREIGN KEY (`idusuario`)
    REFERENCES `mydb`.`usuario` (`idusuario`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `mydb`.`retiros` (
  `idretiro` INT NOT NULL AUTO_INCREMENT,
  `saldoinicial` DOUBLE NOT NULL,
  `saldofinal` DOUBLE NOT NULL,
  `monto` DOUBLE NOT NULL,
  `fecha` VARCHAR(20) NULL,
  `idusuario` INT NOT NULL,
  PRIMARY KEY (`idretiro`),
  INDEX `fk_retiros_usuario1_idx` (`idusuario` ASC),
  CONSTRAINT `fk_retiros_usuario1`
    FOREIGN KEY (`idusuario`)
    REFERENCES `mydb`.`usuario` (`idusuario`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS `mydb`.`administrador` (
  `idadministrador` INT NOT NULL AUTO_INCREMENT,
  `nombre` VARCHAR(45) NOT NULL,
  `alias` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NULL,
  PRIMARY KEY (`idadministrador`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
