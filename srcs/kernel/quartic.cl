// thanks to anroche for providing us his quartic & cubics solvers
// https://github.com/anroche
// https://github.com/anroche/quartic_solver

double3 ft_solve_3(double a, double b, double c, double d)
{
 double a1 = c / d;
 double a2 = b / d;
 double a3 = a / d;
 double3 Result;
 double Q = (a1 * a1 - 3.0 * a2) / 9.0;
 double R = (2.0 * a1 * a1 * a1 - 9.0 * a1 * a2 + 27.0 * a3) / 54.0;
 double Qcubed = Q * Q * Q;
 d = Qcubed - R * R;
 if ( d >= 0.0001 )
 {	// Three real roots
     if ( Q < 0.0 )
     {
       Result[0] = 0;
       Result[1] = 0;
       Result[2] = 0;
	     return (Result);
     }
     double theta = acos(R / sqrt(Qcubed));
     double sqrtQ = sqrt(Q);
     Result[0] = -2.0 * sqrtQ * cos(theta / 3.0) - a1 / 3.0;
     Result[1] = -2.0 * sqrtQ * cos((theta + 2.0 * M_PI) / 3.0 ) - a1 / 3.0;
     Result[2] = -2.0 * sqrtQ * cos((theta + 4.0 * M_PI) / 3.0 ) - a1 / 3.0;
 }
 else
 {	// One real root
     double e = pow(sqrt(-d) + fabs(R), 1.0 / 3.0);
     if ( R > 0 )
         e = -e;
     Result[0] = Result[1] = Result[2] = (e + Q / e) - a1 / 3.0;
 }
 return (Result);
}

int 	ft_solve_4(double t[5], double4 *res)
{
  double3 roots;
  double a0;
  double a1;
	double a2;
	double  a3;
	double	b0;
	double	b1;
	double	b2;
	double	y;
 	double R;
 	double D;
 	double E;
	a0= t[0] / t[4];
  a1 = t[1] / t[4];
  a2 = t[2] / t[4];
  a3 = t[3] / t[4];
  b0 = 4.0 * a2 * a0 - a1 * a1 - a3 * a3 * a0;
  b1 = a1 * a3 - 4.0 * a0;
  b2 = -a2;
	roots = ft_solve_3(b0, b1, b2, 1.0);
  y = max(roots[0], max(roots[1], roots[2]));
	R = 0.25 * a3 * a3 - a2 + y;
  if ( R < 0.0 )
    return (0);
  R = sqrt( R );
  if ( R == 0.0 )
  {
      D = sqrt( 0.75 * a3 * a3 - 2.0 * a2 + 2.0 * sqrt( y * y - 4.0 * a0 ) );
      E = sqrt( 0.75 * a3 * a3 - 2.0 * a2 - 2.0 * sqrt( y * y - 4.0 * a0 ) );
  }
  else
  {
      double Rsquare = R * R;
      double Rrec = 1.0 / R;
      D = sqrt( 0.75 * a3 * a3 - Rsquare - 2.0 * a2 + 0.25 * Rrec * (4.0 * a3 * a2 - 8.0 * a1 - a3 * a3 * a3) );
      E = sqrt( 0.75 * a3 * a3 - Rsquare - 2.0 * a2 - 0.25 * Rrec * (4.0 * a3 * a2 - 8.0 * a1 - a3 * a3 * a3) );
  }
  res->x = -0.25 * a3 + 0.5 * R + 0.5 * D;
  res->y = -0.25 * a3 + 0.5 * R - 0.5 * D;
  res->z =  -0.25 * a3 - 0.5 * R + 0.5 * E;
  res->w = -0.25 * a3 - 0.5 * R - 0.5 * E;
  return (1);
}
