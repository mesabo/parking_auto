//
// Created by mesabo on 13/04/2021.
//

#ifndef PARKINGAUTOTO_LISTERPLACES_H
#define PARKINGAUTOTO_LISTERPLACES_H

extern void listerplaces(MYSQL *con);

extern void listerplacesdisponibles(MYSQL *con);

extern void listerplacesvoituresdisponibles(MYSQL *con);

void listerplacescamionsdisponibles(MYSQL *con);

extern void listerplacesdeuxrouesdisponibles(MYSQL *con);

extern void listerplacesoccupees(MYSQL *con);

#endif //PARKINGAUTOTO_LISTERPLACES_H
