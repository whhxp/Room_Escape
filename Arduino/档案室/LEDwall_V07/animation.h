#ifndef ANIMATION_H

#define ANIMATION_H//一般是文件名的大写 头文件结尾写上一行：
#include <Arduino.h>


short locked[4] = {
  0x007e,0x7a4a,0x7a7e,0x0000};
//0x007e,0x007e,0x5e7e,0x
short unlock[4] = {
  0x007b,0x7949,0x797f,0x0000};
//0x00ce,0x9e92,0x9e92,0x0000
//0x00	0x7e	0x7a	0x4a	0x7a	0x7e	0x00	0x00
//0x00	0x7b	0x79	0x49	0x79	0x7f	0x00	0x00
short empty[]={
  0,0,0,0};
short u[]={
  0xffff,0xc0c0,0xc0c0,0xffff};  
short v[]={
  0x073f,0x78c0,0xc078,0x3f07};  
short door_open0[]={
  0x0000,0x0018,0x1800,0x0000};  
short  door_open1[]={
  0x0000,0x3c24,0x243c,0x0000};  
short door_open2[]={
  0x007e,0x4242,0x4242,0x7e00};  
short door_open3[]={
  0xff81,0x8181,0x8181,0x81ff}; 
short door_open3_1[]={
  0x8181,0x8181,0x8181,0x8181}; 
short door_open_l_1[]={
  0xffff,0x0000,0x0000,0x0000};
short door_open_l_2[]={
  0x8181,0xffff,0x0000,0x0000};
short door_open_l_3[]={
  0x8181,0x8181,0xffff,0x0000};
short door_open_l_4[]={
  0x8181,0x8181,0x8181,0xffff};
short door_open_r_1[]={
  0x0000,0x0000,0x0000,0xffff};  
short door_open_r_2[]={
  0,0x0000,0xffff,0x8181};
short door_open_r_3[]={
  0,0xffff,0x8181,0x8181};
short door_open_r_4[]={
  0xffff,0x8181,0x8181,0x8181};
#endif

