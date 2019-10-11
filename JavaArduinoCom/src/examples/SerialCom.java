package examples;

import java.util.Scanner;

import arduino.*;

public class SerialCom {

	public static void main(String[] args) {
		
		Scanner ob = new Scanner(System.in);
		Arduino arduino = new Arduino("inserte puerto", 9600); //enter the port name here, and ensure that Arduino is connected, otherwise exception will be thrown.
		arduino.openConnection();
		System.out.println("Inserte instrucciones");
		String input = ob.nextLine();
		while(input != "salir") {
		arduino.serialWrite(input);
		input = ob.nextLine();
		}
		ob.close();
		arduino.closeConnection();
		

	}

}
