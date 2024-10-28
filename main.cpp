#include "DataBase.h"
#include "Client.h"
#include "Vehicle.h"
#include "Error.h"

#include <fstream>
#include <cstdint>
#include <iostream>
#include <list>

using namespace std;

int main() {
    Client c1(0, "Juan Perez", 30, 84058485,  "aasdasd", "juan@example.com", "123456789", "ABC123", "Sedan", "Rojo", "Toyota", "Corolla");
    Client c2(25, "Maria Gomez", 28, 47938475,  "BAvenida Siempre Viva 742", "maria@example.com", "987654321", "XYZ456", "SUV", "Azul", "Ford", "Escape");
    Client c3(3, "Carlos Ruiz", 35, 76583927, "CBoulevard de los sueños 456", "carlos@example.com", "123123123", "LMN789", "Camioneta", "Negro", "Chevrolet", "S10");
    Client c4(4, "Ana Torres", 22, 56787456,  "DCalle de la Paz 321", "ana@example.com", "456456456", "DEF101", "Hatchback", "Verde", "Volkswagen", "Polo");
    Client c5(5, "Pedro Martinez", 40,44564345,   "ECalle Larga 789", "pedro@example.com", "321321321", "GHI112", "Convertible", "Amarillo", "Mazda", "MX-5");
    Client c6(6, "Lucia Sanchez", 27, 58987234,   "FCalle Cortada 654", "lucia@example.com", "654654654", "JKL131", "Sedan", "Blanco", "Nissan", "Altima");
    Client c7(7, "Javier Lopez", 32, 39207456,   "GCalle del Sol 852", "javier@example.com", "789789789", "MNO145", "Coupe", "Gris", "Honda", "Civic");
    Client c8(8, "Sofia Martinez", 29, 32657483,   "Avenida del Mar 963", "sofia@example.com", "321987321", "PQR159", "Pickup", "Café", "Toyota", "Tacoma");
    Client c9(9, "Diego Fernandez", 45, 48398573,   "HCalle de la Amistad 159", "diego@example.com", "852369741", "STU168", "SUV", "Negro", "Hyundai", "Tucson");
    Client c10(10, "Valentina Salas", 26, 45490372, "ICalle de los Sueños 258", "valentina@example.com", "753951852", "VWX174", "Hatchback", "Rojo", "Kia", "Forte");
    		
    DataBase db("SAPEI.db");

    db.addClient(c1);
    db.addClient(c2);
    db.addClient(c3);
    db.addClient(c4);
    db.addClient(c5);
    db.addClient(c6);
    db.addClient(c7);
    db.addClient(c8);
    db.addClient(c9);
    db.addClient(c10);


    cout << db.getClientById(6) << endl;
    cout << db.getClientByName("Ana Torres") << endl;

    db.showClients();

    db.exportClientsToCSV();
    
    //list <Client> listClients;
    //setClientToList(listClients,c1);
    
   //string listaclientes  = getClients(listClients);
    return 0;

}
