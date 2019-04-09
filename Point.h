#ifndef Point_h
#define Point_h

///	\file Point.c
/// \brief Header de la classe point.
/// \author M. Bardin, A. Canton Condes, A. Lamouchi, M. Lin-Wee-Kuan
/// \version 0.1
/// \date 9 avril 2019
///
/// Header de la classe point déclarant par ailleurs les méthodes diverge et converge.
///

/// \class point Point.h
/// \brief A COMPLETER
/// 
class point
{
private:
	double x; /*< abscisse */
	double y; /*< ordonnée */

public:
/// \fn point (double X = 0, double Y = 0)
/// \brief Fonction A COMPLETER.
/// \param x : coordonnée d'abscisse du point.
/// \param y : coordonnée d'ordonnée du point.
/// \return A COMPLETER.
///
	point(double X = 0, double Y = 0);

/// \fn double getX () const
/// \brief Fonction A COMPLETER.
/// \return A COMPLETER.
///
	double getX() const;

/// \fn double getY () const
/// \brief Fonction A COMPLETER.
/// \return A COMPLETER.
///
	double getY() const;

/// \fn void setX (double x)
/// \brief Fonction A COMPLETER.
/// \param x : coordonnée d'abscisse du point.
///
	void setX(double x);

/// \fn void setY(double y)
/// \brief Fonction A COMPLETER.
/// \param y : coordonnée d'ordonnée du point.
///
	void setY(double y);

/// \fn static int diverge (double x, double y)
/// \brief Fonction A COMPLETER.
/// \param x : coordonnée d'abscisse du point.
/// \param y : coordonnée d'ordonnée du point.
/// \return A COMPLETER.
///
	static int diverge(double x, double y);

/// \fn point converge (double x, double y)
/// \brief Fonction A COMPLETER.
/// \param x : coordonnée d'abscisse du point.
/// \param y : coordonnée d'ordonnée du point.
/// \return A COMPLETER.
///
	static point converge(double x, double y);

/// \fn point& operator= (const point &p)
/// \brief Opérateur d'affectation de point.
/// \param p : le point que l'on veut affecter à notre point.
/// \return Renvoie notre point.
///
	point& operator=(const point &p);

};

#endif