//
// Created by mesabo on 16/04/2021.
//

#ifndef GESTION_PARKING_AUTO_POPULATE_H
#define GESTION_PARKING_AUTO_POPULATE_H

void createdatabase(MYSQL *con);

void insert_vehicule(MYSQL *con);

void insert_camions(MYSQL *con);

void insert_2roues(MYSQL *con);

#endif //GESTION_PARKING_AUTO_POPULATE_H
