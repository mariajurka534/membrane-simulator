#include "Membrane.hpp"
#include <cmath>

  
    double Membrane::getWidth() const{
        return width;
    }
    double Membrane::getLength() const{
        return length;
    }
    double Membrane::getTension() const{
        return tension;
    }
    double Membrane::getSMD() const{
        return surface_mass_density;
    }
    int Membrane::getGridLength() const{
        return gridLength;
    }
    int Membrane::getGridWidth() const{
        return gridWidth;
    }
   

    void Membrane::setWidth(double width){
        if(width <= 0){
            throw std::invalid_argument("invalid argument");
        }
        this->width = width;
    };
    void Membrane::setLength(double length){
        if(length <= 0){
            throw std::invalid_argument("invalid argument");
        }
        this->length = length;
    };
    void Membrane::setTension(double tension){
        if(tension <= 0){
            throw std::invalid_argument("invalid argument");
        }
        this->tension = tension;
    };
    void Membrane::setSMD(double surface_mass_density){
        if(surface_mass_density <= 0){
            throw std::invalid_argument("invalid argument");
        }
        this->surface_mass_density = surface_mass_density;
    };
    // void Membrane::setGridLength(int gridLength);
    // void Membrane::setGridWidth(int gridWidth);


    double Membrane::getDisplacement(int x, int y) const{

        if(x < 0 || y < 0 || x >= gridLength || y >= gridWidth){
            throw std::invalid_argument("invalid argument(s)");
        }

        return displacement[x][y];
    };

    void Membrane::setDisplacement(int x, int y, double value){

        if(x < 0 || y < 0 || x >= gridLength || y >= gridWidth){
            throw std::invalid_argument("invalid argument(s)");
        }

        displacement[x][y] = value;
    };

    // wave speed determiens how quickly a disturbance travels
    // actoss the membrane
    double Membrane::waveSpeed() const{
        return std::sqrt(tension/surface_mass_density);
    };

