//
// Created by mesabo on 13/04/2021.
//

#ifndef PARKINGAUTOTO_MARQUERPLACE_H
#define PARKINGAUTOTO_MARQUERPLACE_H

extern void occuperplace(MYSQL *con, char code[50]);

extern void libererplace(MYSQL *con, char code[50]);

#endif //PARKINGAUTOTO_MARQUERPLACE_H
