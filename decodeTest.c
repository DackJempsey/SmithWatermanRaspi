/*
 * UncodeTest.c
 * 
 * Copyright 2018 Jack Dempsey <jackdempsey@rgnt2-102-74-dhcp.int.colorado.edu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>


char unpack(unsigned int encode,int i){//takes the integer and unpacks that into an array of characters
	char out;
	
	unsigned int transfer;
	
	
	transfer = encode << i;
	transfer = transfer >> 30 ;

	printf("Encoded:%d Transfer:%d:: \n",encode,transfer);
	
	switch(transfer){
		case 0:
			out = 'A';
			break;
		case 1:
			out= 'C';
			break;
		case 2:
			out = 'G';
			break;
		case 3:
			out= 'T';
			break;
		default:
			out ='X';
			break;
	}
	
	return out;
	
	
}

int main(int argc, char **argv)
{
	for(int i =0;i<31;i+=2){
	printf("%c \n",unpack(1431655764,i));
}
	
	return 0;
}

