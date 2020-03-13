/*
 * Example of `adapter' design pattern
 * Copyright (C) 2011 Radek Pazdera

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>

typedef int Cable; // Cable con electrones

/* Interface Adaptado (fuente) */
class InterfaceEnchufeEuropeo
{
    public:
        virtual int voltaje() = 0;

        virtual Cable vivo() = 0;
        virtual Cable neutral() = 0;
        virtual Cable tierra() = 0;
};

/* Adaptado */
class Enchufe : public InterfaceEnchufeEuropeo
{
    public:
        int voltaje() { return 220; }

        Cable vivo() { return 1; }
        Cable neutral() { return -1; }
        Cable tierra() { return 0; }
};

/* Interface Objetivo */
class InterfaceEnchufeUSA
{
    public:
        virtual int voltaje() = 0;

        virtual Cable vivo() = 0;
        virtual Cable neutral() = 0;
};

/* Adaptador*/
class Adaptador : public InterfaceEnchufeUSA
{
    InterfaceEnchufeEuropeo* enchufe;

    public:
        void Enchufar(InterfaceEnchufeEuropeo* TomaCorriente)
        {
            enchufe = TomaCorriente;
        }

        int voltaje() { return 110; }
        Cable vivo() { return enchufe->vivo(); }
        Cable neutral() { return enchufe->neutral(); }
};

/* Cliente */
class TeteraElectrica
{
    InterfaceEnchufeUSA* energia;

    public:
        void Enchufar(InterfaceEnchufeUSA* suministrar)
        {
            energia = suministrar;
        }

        void Hervir()
        {
            if (energia->voltaje() > 110)
            {
                std::cout << "La tetera está en llamas!" << std::endl;
                return;
            }

            if (energia->vivo() == 1 && energia->neutral() == -1)
            {
                std::cout << "Es hora del cafe!" << std::endl;
            }
        }
};


int main()
{
    Enchufe* enchufe = new Enchufe;
    Adaptador* adaptador = new Adaptador;
    TeteraElectrica* Tetera = new TeteraElectrica;

    /* Conectando. */
    adaptador->Enchufar(enchufe);
    Tetera->Enchufar(adaptador);

    /* Haciendo cafe */
    Tetera->Hervir();

    return 0;
}


