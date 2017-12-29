/*
Navicat MySQL Data Transfer

Source Server         : 192.168.1.144
Source Server Version : 50554
Source Host           : 192.168.1.144:3306
Source Database       : db_ir

Target Server Type    : MYSQL
Target Server Version : 50554
File Encoding         : 65001

Date: 2017-12-29 10:23:25
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for table_brand_list
-- ----------------------------
DROP TABLE IF EXISTS `table_brand_list`;
CREATE TABLE `table_brand_list` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `brand_name` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for table_function_list
-- ----------------------------
DROP TABLE IF EXISTS `table_function_list`;
CREATE TABLE `table_function_list` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `function_name` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for table_good_list
-- ----------------------------
DROP TABLE IF EXISTS `table_good_list`;
CREATE TABLE `table_good_list` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `function` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `type` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `num` tinyint(4) DEFAULT NULL,
  `cost_price` float(10,2) DEFAULT NULL,
  `sale_price` float(10,2) DEFAULT NULL,
  `sale` tinyint(4) DEFAULT NULL,
  `worker` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `timeval` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=215 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for table_sale_list
-- ----------------------------
DROP TABLE IF EXISTS `table_sale_list`;
CREATE TABLE `table_sale_list` (
  `id` int(11) NOT NULL,
  `name` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `function` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `type` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `customer` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `num` tinyint(4) DEFAULT NULL,
  `cost_price` decimal(10,0) DEFAULT NULL,
  `sale_price` decimal(10,0) DEFAULT NULL,
  `phone` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `address` char(255) CHARACTER SET gbk DEFAULT NULL,
  `saler` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  `timeval` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for table_type_list
-- ----------------------------
DROP TABLE IF EXISTS `table_type_list`;
CREATE TABLE `table_type_list` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `type_name` varchar(255) CHARACTER SET gbk DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
