#include "decide.h"
#include <cmath>
#include <cstdio>

COMPTYPE Decide::DOUBLECOMPARE(double a, double b) const {
  if (fabs(a - b) < 0.000001)
    return EQ;
  if (a < b)
    return LT;
  return GT;
}

/// @brief Computes the angle (in degrees) between three points, where the
/// second point is the vertex
/// @param point1 first point
/// @param point2 second point, the vertex
/// @param point3 third point
/// @return returns the angle (in degrees) created by the three points.

double Decide::COMPUTEANLGE(const COORDINATE &point1, const COORDINATE &point2,
                            const COORDINATE &point3) {
  // calculate vectors to form the angle
  COORDINATE v1 = {point1.x - point2.x,
                   point1.y - point2.y}; // vector from p2 to p1
  COORDINATE v2 = {point3.x - point2.x,
                   point3.y - point2.y}; // vector from p2 to p3

  // using dot product formula to get the angle:
  // calculate the vector multiplication
  double dot_product = v1.x * v2.x + v1.y * v2.y;

  // calcualte the vectors magnitude
  double magnitude_v1 = std::sqrt(std::pow(v1.x, 2) + std::pow(v1.y, 2));
  double magnitude_v2 = std::sqrt(std::pow(v2.x, 2) + std::pow(v2.y, 2));

  // get the angle from the dot product formula
  double angle = std::acos(dot_product / (magnitude_v1 * magnitude_v2));

  // convert angle from radians to degrees
  // angle = angle * 180.0 / PI;
  return angle;
}

/// @brief Validates that an angle can be made with the three points provided
/// @param point1 first point
/// @param point2 second point, the vertex
/// @param point3 third point
/// @return returns True if an angle can be made, returns False if an angle is
/// undefined
bool Decide::VALIDATEANGLE(const COORDINATE &point1, const COORDINATE &point2,
                           const COORDINATE &point3) {
  // return ((point1.x == point2.x && point1.y == point2.y) ||
  //         (point3.x == point2.x && point3.y == point2.y));

  return ((point1.x != point2.x || point1.y != point2.y) &&
          (point3.x != point2.x || point3.y != point2.y));
}

Decide::Decide(int NUMPOINTS, const std::vector<COORDINATE> &POINTS,
               const PARAMETERS_T &PARAMETERS,
               const std::array<std::array<CONNECTORS, 15>, 15> &LCM,
               const std::array<bool, 15> &PUV)
    : NUMPOINTS(NUMPOINTS), COORDINATES(POINTS), PARAMETERS(PARAMETERS),
      LCM(LCM), PUV(PUV) {}

void Decide::debugprint() const {
  printf("Coordinates (x, y):\n");
  for (int i = 0; i < NUMPOINTS; ++i) {
    printf("\t(%f, %f)\n", COORDINATES[i].x, COORDINATES[i].y);
  }

  printf("\nParameters:\n");

  printf("\tLENGTH1: %f\n", PARAMETERS.LENGTH1);
  printf("\tRADIUS1: %f\n", PARAMETERS.RADIUS1);
  printf("\tEPSILON: %f\n", PARAMETERS.EPSILON);
  printf("\tAREA1: %f\n", PARAMETERS.AREA1);
  printf("\tQ_PTS: %d\n", PARAMETERS.Q_PTS);
  printf("\tQUADS: %d\n", PARAMETERS.QUADS);
  printf("\tDIST: %f\n", PARAMETERS.DIST);
  printf("\tN_PTS: %d\n", PARAMETERS.N_PTS);
  printf("\tK_PTS: %d\n", PARAMETERS.K_PTS);
  printf("\tB_PTS: %d\n", PARAMETERS.A_PTS);
  printf("\tB_PTS: %d\n", PARAMETERS.B_PTS);
  printf("\tC_PTS: %d\n", PARAMETERS.C_PTS);
  printf("\tD_PTS: %d\n", PARAMETERS.D_PTS);
  printf("\tE_PTS: %d\n", PARAMETERS.E_PTS);
  printf("\tF_PTS: %d\n", PARAMETERS.F_PTS);
  printf("\tG_PTS: %d\n", PARAMETERS.G_PTS);
  printf("\tLENGTH2: %f\n", PARAMETERS.LENGTH2);
  printf("\tRADIUS2: %f\n", PARAMETERS.RADIUS2);
  printf("\tAREA2: %f\n", PARAMETERS.AREA2);

  printf("\nLCM:\n");

  for (int y = 0; y < 15; ++y) {
    printf("\t");
    for (int x = 0; x < 15; ++x) {
      printf("%s ", LCM[y][x] == NOTUSED
                        ? "NOTUSED"
                        : (LCM[y][x] == ANDD ? "ANDD   " : "ORR    "));
    }
    printf("\n");
  }

  printf("\nPUV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", PUV[i] ? "true" : "false");
  }

  printf("\nCMV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", CMV[i] ? "true" : "false");
  }

  printf("\n\nPUM:\n");
  for (int y = 0; y < 15; ++y) {
    printf("\t");
    for (int x = 0; x < 15; ++x) {
      printf("%s ", PUM[y][x] ? "true " : "false");
    }
    printf("\n");
  }

  printf("\nFUV:\n\t");
  for (int i = 0; i < 15; ++i) {
    printf("%s ", FUV[i] ? "true" : "false");
  }

  printf("\n\nLAUNCH:\n\t%s\n", LAUNCH ? "true" : "false");
}

void Decide::Calc_CMV() {
  Decide::CMV[0] = Lic0();
  Decide::CMV[1] = Lic1();
  Decide::CMV[2] = Lic2();
  Decide::CMV[3] = Lic3();
  Decide::CMV[4] = Lic4();
  Decide::CMV[5] = Lic5();
  Decide::CMV[6] = Lic6();
  Decide::CMV[7] = Lic7();
  Decide::CMV[8] = Lic8();
  Decide::CMV[9] = Lic9();
  Decide::CMV[10] = Lic10();
  Decide::CMV[11] = Lic11();
  Decide::CMV[12] = Lic12();
  Decide::CMV[13] = Lic13();
  Decide::CMV[14] = Lic14();
}

/**
 * @brief There exists at least one set of two consecutive data points that are
 a distance greater than the length, LENGTH1, apart. (0 ≤ LENGTH1)

 * @return true
 * @return false
 */

bool Decide::Lic0() {
  // Iterate through consecutive pairs of points
  for (int i = 0; i < NUMPOINTS - 1; ++i) {
    // Calculate the distance between consecutive points
    double distance = sqrt(pow(COORDINATES[i + 1].x - COORDINATES[i].x, 2) +
                           pow(COORDINATES[i + 1].y - COORDINATES[i].y, 2));

    // Check if the distance is greater than LENGTH1
    if (DOUBLECOMPARE(distance, PARAMETERS.LENGTH1) == GT) {
      // Set the corresponding CMV element to true
      return true;
    }
  }
  return false;
}

/**
 * @brief There exists at least one set of three consecutive data points that
 * cannot all be contained within or on a circle of radius RADIUS1.
 * (0 ≤ RADIUS1)
 *
 * https://artofproblemsolving.com/wiki/index.php/Circumradius
 */

bool Decide::Lic1() {
  for (int i = 0; i < NUMPOINTS - 2; ++i) {
    COORDINATE p1 = COORDINATES[i];
    COORDINATE p2 = COORDINATES[i + 1];
    COORDINATE p3 = COORDINATES[i + 2];

    // find the size of the triangle
    double a = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    double b = sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2));
    double c = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));

    double s = (a + b + c) / 2;

    double area = sqrt(s * (s - a) * (s - b) * (s - c)); // Heron's formula

    if (DOUBLECOMPARE(area, 0) == EQ) {
      double max = std::max(std::max(a, b), c);
      if (DOUBLECOMPARE(max, PARAMETERS.RADIUS1) == GT) {
        return true;
      }
    } else {
      double r = (a * b * c) / (4 * area); // radius of the circumcircle

      if (DOUBLECOMPARE(r, PARAMETERS.RADIUS1) == GT) {
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief There exists at least one set of three consecutive data points which
 form an angle such that: angle < (PI−EPSILON) or angle > (PI+EPSILON) The
 second of the three consecutive points is always the vertex of the angle. If
 either the first point or the last point (or both) coincides with the vertex,
 the angle is undefined and the LIC is not satisfied by those three points. (0 ≤
 EPSILON < PI)
 *
 * @return true
 * @return false
 */

bool Decide::Lic2() {
  // CONDITION: find three consecutive data points to form an angle with
  //            angle needs to be in range to enable LIC
  const double &EPSILON = PARAMETERS.EPSILON;

  // -2 to prevent index error
  for (int i = 0; i < NUMPOINTS - 2; ++i) {
    // create reference to coordinates, const to protect changes
    const COORDINATE &point1 = COORDINATES[i];
    const COORDINATE &point2 = COORDINATES[i + 1];
    const COORDINATE &point3 = COORDINATES[i + 2];

    // the second point is the "vertex", if any point coincides with it
    // the angle is undefined, therfore is invalid
    if (VALIDATEANGLE(point1, point2, point3) == false) {
      continue;
    }
    // otherwise...
    double angle = COMPUTEANLGE(point1, point2, point3);
    // using DOUBLECOMPARE to check angle against pi - epsilon
    if ((DOUBLECOMPARE(angle, PI - EPSILON) == LT ||
         DOUBLECOMPARE(angle, PI + EPSILON) == GT)) {
      // we found a valid angle! set corresponding CMV to true
      return true;
    }
  }

  // set the corresponding Conditions Met Vector
  return false;
}

/**
 * @brief There exists at least one set of three consecutive data points that
 are the vertices of a triangle with area greater than AREA1. (0 ≤ AREA1)

 * @return true
 * @return false
 */

bool Decide::Lic3() {
  bool found_greater_area = false;

  for (size_t i = 0; i < COORDINATES.size() - 2; ++i) {
    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + 1];
    COORDINATE c3 = COORDINATES[i + 2];

    // Formula from:
    // https://www.cuemath.com/geometry/area-of-triangle-in-coordinate-geometry/
    double area = 0.5 * fabs(c1.x * (c2.y - c3.y) + c2.x * (c3.y - c1.y) +
                             c3.x * (c1.y - c2.y));

    COMPTYPE comp = DOUBLECOMPARE(area, PARAMETERS.AREA1);

    if (comp == GT) {
      found_greater_area = true;
      break;
    }
  }

  return found_greater_area;
}

/**
 * @brief There exists at least one set of Q_PTS consecutive data points that
 lie in more than QUADS quadrants. Where there is ambiguity as to which quadrant
 contains a given point, priority of decision will be by quadrant number, i.e.,
 I, II, III, IV. For example, the data point (0,0) is in quadrant I, the point
 (-l,0) is in quadrant II, the point (0,-l) is in quadrant III, the point (0,1)
 is in quadrant I and the point (1,0) is in quadrant I. (2 ≤ Q PTS ≤ NUMPOINTS),
 (1 ≤ QUADS ≤ 3)

 *
 * @return true
 * @return false
 */

bool Decide::Lic4() {
  if (NUMPOINTS < PARAMETERS.Q_PTS)
    return false;

  for (int i = 0; i < NUMPOINTS - PARAMETERS.Q_PTS + 1; i++) {
    bool quadrants[4];
    for (int k = 0; k < 4; k++) {
      quadrants[k] = false;
    }

    int count = 0;
    for (int j = 0; j < PARAMETERS.Q_PTS; j++) {
      COORDINATE p = COORDINATES[i + j];
      // if (p.x >= 0) {
      if (DOUBLECOMPARE(p.x, 0.0) != LT) {
        // if (p.y >= 0) {
        if (DOUBLECOMPARE(p.y, 0.0) != LT) {
          quadrants[0] = true;
        } else {
          quadrants[3] = true;
        }
      } else {
        if (DOUBLECOMPARE(p.y, 0.0) != LT) {
          quadrants[1] = true;
        } else {
          quadrants[2] = true;
        }
      }
    }
    for (bool q : quadrants) {
      if (q) {
        count += 1;
      }
    }
    if (count > PARAMETERS.QUADS) {
      return true;
    }
  }
  return false;
}

/**
 * @brief There exists at least one set of two consecutive data points,
 (X[i],Y[i]) and (X[j],Y[j]), such that X[j] - X[i] < 0. (where i = j-1)
 *
 * @return true
 * @return false
 */
bool Decide::Lic5() {
  // Iterate through consecutive pairs of data points
  for (int i = 0; i < NUMPOINTS - 1; i++) {
    //// Check if X[j] - X[i] < 0
    if (DOUBLECOMPARE(COORDINATES[i + 1].x - COORDINATES[i].x, 0) == LT) {
      // The condition is met, set CMV[4] to true
      return true;
    }
  }

  return false;
}

/**
 * @brief There exists at least one set of N_PTS consecutive data points such
 * that at least one of the points lies a distance greater than DIST from the
 * line joining the first and last of these N_PTS points. If the first and last
 * points of these N_PTS are identical, then the calculated distance to compare
 * with DIST will be the distance from the coincident point to all other points
 * of the N_PTS consecutive points. The condition is not met when NUMPOINTS < 3.
 *
 */
bool Decide::Lic6() {
  if (NUMPOINTS < 3) {
    return false;
  }

  for (int i = 0; i < NUMPOINTS - PARAMETERS.N_PTS + 1; ++i) {
    COORDINATE p1 = COORDINATES[i];
    COORDINATE p2 = COORDINATES[i + PARAMETERS.N_PTS];

    if (DOUBLECOMPARE(p1.x, p2.x) == EQ && DOUBLECOMPARE(p1.y, p2.y) == EQ) {
      // p1 and p2 are the same point
      for (int j = 0; j < NUMPOINTS; ++j) {
        if (j == i)
          continue;

        COORDINATE p3 = COORDINATES[j];

        double distance = sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));

        if (DOUBLECOMPARE(distance, PARAMETERS.DIST) == GT) {
          return true;
        }
      }
    } else {
      // p1 and p2 are different points
      for (int j = 0; j < NUMPOINTS; ++j) {
        if (j == i || j == i + PARAMETERS.N_PTS - 1)
          continue;

        COORDINATE p3 = COORDINATES[j];
        // https://math.stackexchange.com/questions/2757318/distance-between-a-point-and-a-line-defined-by-2-points
        double distance = fabs((p2.x - p1.x) * (p3.y - p1.y) -
                               (p3.x - p1.x) * (p2.y - p1.y)) /
                          sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));

        if (DOUBLECOMPARE(distance, PARAMETERS.DIST) == GT) {
          return true;
        }
      }
    }
  }
  return false;
}

/**
 * @brief There exists at least one set of two data points separated by exactly
 K PTS consecutive
 * intervening points that are a distance greater than the length, LENGTH1,
 apart. The condition is not met when NUMPOINTS < 3. 1 ≤ K PTS ≤ (NUMPOINTS−2)

 *
 * @return true
 * @return false
 */
bool Decide::Lic7() {
  // create references
  const int &K_PTS = PARAMETERS.K_PTS;

  // condition not met when NUMPOINTS less than three
  if (NUMPOINTS >= 3) {
    // we need to check two data points seperated by K_PTS steps
    // reduce number of points to explore to prevent index error
    for (int i = 0; i < NUMPOINTS - K_PTS - 1; i++) {
      // get the difference between current coordinate and coordinate K_PTS + 1
      // points ahead K_PTS + 1 because we want exactly K_PTS points BETWEEN, so
      // K_PTS nodes between i and i + (K_PTS + 1)
      double dx = COORDINATES[i + K_PTS + 1].x - COORDINATES[i].x;
      double dy = COORDINATES[i + K_PTS + 1].y - COORDINATES[i].y;
      double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));

      if (DOUBLECOMPARE(distance, PARAMETERS.LENGTH1) == GT) {
        return true;
      }
    }
  }

  // set the corresponding Conditions Met Vector
  return false;
}

/**
 * @brief There exists at least one set of three data points separated by
 exactly A PTS and B PTS consecutive intervening points, respectively, that
 cannot be contained within or on a circle of radius RADIUS1. The condition is
 not met when NUMPOINTS < 5. 1 ≤ A PTS, 1 ≤ B PTS A PTS+B PTS ≤ (NUMPOINTS−3)

 *
 * @return true
 * @return false
 */

bool Decide::Lic8() {
  if (NUMPOINTS < 5) {
    return false;
  }

  bool found_larger_triangle = false;

  auto dist_lambda = [](const COORDINATE &a, const COORDINATE &b) -> double {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  };

  for (int i = 0; i < NUMPOINTS; ++i) {
    if (i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2 >= NUMPOINTS) {
      break;
    }

    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + PARAMETERS.A_PTS + 1];
    COORDINATE c3 = COORDINATES[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2];

    double a = dist_lambda(c1, c2);
    double b = dist_lambda(c1, c3);
    double c = dist_lambda(c2, c3);

    // Based on this formula:
    // https://mathworld.wolfram.com/Circumradius.html
    double circumradius = (a * b * c) / sqrt((a + b + c) * (b + c - a) *
                                             (c + a - b) * (a + b - c));

    COMPTYPE comp = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS1);

    if (comp == GT) {
      found_larger_triangle = true;
      break;
    }
  }

  return found_larger_triangle;
}

/**
 * @brief There exists at least one set of three data points separated by
 exactly C PTS and D PTS consecutive intervening points, respectively, that form
 an angle such that: angle < (PI−EPSILON) or angle > (PI+EPSILON) The second
 point of the set of three points is always the vertex of the angle. If either
 the first point or the last point (or both) coincide with the vertex, the angle
 is undefined and the LIC is not satisfied by those three points. When NUMPOINTS
 < 5, the condition is not met. 1 ≤ C PTS, 1 ≤ D PTS C PTS+D PTS ≤ NUMPOINTS−3
 *
 * @return true
 * @return false
 */

bool Decide::Lic9() {
  if (NUMPOINTS < 5)
    return false;
  std::vector<COORDINATE> a;
  for (int i = 0; i < NUMPOINTS - 2 - PARAMETERS.C_PTS - PARAMETERS.D_PTS;
       i++) {
    a.clear();
    a.push_back(COORDINATES[i]);
    a.push_back(COORDINATES[i + PARAMETERS.C_PTS + 1]);
    a.push_back(COORDINATES[i + PARAMETERS.C_PTS + PARAMETERS.D_PTS + 2]);

    if (VALIDATEANGLE(a[0], a[1], a[2]) == false)
      continue;

    double angle = COMPUTEANLGE(a[0], a[1], a[2]);

    if (DOUBLECOMPARE(angle, PI - PARAMETERS.EPSILON) == LT ||
        DOUBLECOMPARE(angle, PI + PARAMETERS.EPSILON) == GT) {
      return true;
    }
  }

  return false;
}

/**
 * @brief There exists at least one set of three data points separated by
 exactly E_PTS and F_PTS
 * consecutive intervening points, respectively, that are the vertices of a
 triangle with area greater than AREA1. The condition is not met when NUMPOINTS
 < 5. 1 ≤ E PTS, 1 ≤ F PTS E_PTS + F_PTS ≤ NUMPOINTS−3
 *
 * @return true
 * @return false
 */

bool Decide::Lic10() {
  if (NUMPOINTS < 5) {
    return false;
  }

  for (int i = 0; i < NUMPOINTS; ++i) {

    if (i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2 >= NUMPOINTS) {
      break;
    }

    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + PARAMETERS.E_PTS + 1];
    COORDINATE c3 = COORDINATES[i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2];

    // Calculate the area of the triangle formed by points (i, j, k)
    double area = 0.5 * fabs(c1.x * (c2.y - c3.y) + c2.x * (c3.y - c1.y) +
                             c3.x * (c1.y - c2.y));
    if (DOUBLECOMPARE(area, PARAMETERS.AREA1) == GT) {
      // Set CMV[9] to true if condition is met
      return true;
    }
  }
  return false;
}

/**
 * @brief There exists at least one set of two data points, (X[i],Y[i]) and
 * (X[j],Y[j]), separated by exactly G_PTS consecutive intervening points, such
 * that X[j] - X[i] < 0. (where i < j ) The condition is not met when NUMPOINTS
 * < 3. 1 ≤ G PTS ≤ NUMPOINTS−2
 *
 */
bool Decide::Lic11() {
  if (NUMPOINTS < 3) {
    return false;
  }

  for (int i = 0; i < NUMPOINTS - PARAMETERS.G_PTS - 1; ++i) {
    COORDINATE p1 = COORDINATES[i];
    COORDINATE p2 = COORDINATES[i + PARAMETERS.G_PTS + 1];

    if (DOUBLECOMPARE(p2.x - p1.x, 0) == LT) {
      return true;
    }
  }

  return false;
}

/**
 * @brief There exists at least one set of two data points, separated by exactly
 K PTS consecutive intervening points, which are a distance greater than the
 length, LENGTH1, apart. In addition, there exists at least one set of two data
 points (which can be the same or different from the two data points just
 mentioned), separated by exactly K PTS consecutive intervening points, that are
 a distance less than the length, LENGTH2, apart. Both parts must be true for
 the LIC to be true. The condition is not met when NUMPOINTS < 3. 0 ≤ LENGTH2
 *
 * @return true
 * @return false
 */

bool Decide::Lic12() {
  // create flags for both conditions
  bool condition1 = false;
  bool condition2 = false;
  // create reference
  const int &K_PTS = PARAMETERS.K_PTS;

  // if numpoints < 3, stop!
  if (NUMPOINTS < 3) {
    return false;
  }

  // CODE REUSED FROM LIC7
  for (int i = 0; i < NUMPOINTS - K_PTS - 1; i++) {
    double dx = COORDINATES[i + K_PTS + 1].x - COORDINATES[i].x;
    double dy = COORDINATES[i + K_PTS + 1].y - COORDINATES[i].y;
    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));

    // check condition one
    if (DOUBLECOMPARE(distance, PARAMETERS.LENGTH1) == GT) {
      condition1 = true;
      break;
    }
  }

  for (int i = 0; i < NUMPOINTS - K_PTS - 1; i++) {
    double dx = COORDINATES[i + K_PTS + 1].x - COORDINATES[i].x;
    double dy = COORDINATES[i + K_PTS + 1].y - COORDINATES[i].y;
    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));

    // check condition two
    if (DOUBLECOMPARE(distance, PARAMETERS.LENGTH2) == LT) {
      condition2 = true;
      break;
    }
  }

  // LIC is true only if both conditions are fulfilled
  if (condition1 == true && condition2 == true) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief There exists at least one set of three data points, separated by
exactly A PTS and B PTS consecutive intervening points, respectively, that
cannot be contained within or on a circle of radius RADIUS1. In addition, there
exists at least one set of three data points (which can be the same or different
from the three data points just mentioned) separated by exactly A PTS and B PTS
consecutive intervening points, respectively, that can be contained in or on a
circle of radius RADIUS2. Both parts must be true for the LIC to be true. The
condition is not met when NUMPOINTS < 5. 0 ≤ RADIUS2

 *
 * @return true
 * @return false
 */

bool Decide::Lic13() {
  if (NUMPOINTS < 5) {
    return false;
  }

  bool found_larger_triangle = false;
  bool found_smaller_triangle = false;

  auto dist_lambda = [](const COORDINATE &a, const COORDINATE &b) -> double {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  };

  for (int i = 0; i < NUMPOINTS; ++i) {
    if (i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2 >= NUMPOINTS) {
      break;
    }

    COORDINATE c1 = COORDINATES[i];
    COORDINATE c2 = COORDINATES[i + PARAMETERS.A_PTS + 1];
    COORDINATE c3 = COORDINATES[i + PARAMETERS.A_PTS + PARAMETERS.B_PTS + 2];

    double a = dist_lambda(c1, c2);
    double b = dist_lambda(c1, c3);
    double c = dist_lambda(c2, c3);

    // Based on this formula:
    // https://mathworld.wolfram.com/Circumradius.html
    double circumradius = (a * b * c) / sqrt((a + b + c) * (b + c - a) *
                                             (c + a - b) * (a + b - c));

    COMPTYPE comp1 = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS1);
    COMPTYPE comp2 = DOUBLECOMPARE(circumradius, PARAMETERS.RADIUS2);

    if (comp1 == GT) {
      found_larger_triangle = true;
    }

    if (comp2 != GT) {
      found_smaller_triangle = true;
    }

    if (found_larger_triangle && found_smaller_triangle) {
      break;
    }
  }

  return found_smaller_triangle && found_larger_triangle;
}

/**
 * @brief There exists at least one set of three data points, separated by
 exactly E_PTS and F_PTS
 * consecutive intervening points, respectively, that are the vertices of a
 triangle with area greater than AREA1. In addition, there exist three data
 points (which can be the same or different from the three data points just
 mentioned) separated by exactly E PTS and F PTS consecutive intervening points,
   respectively, that are the vertices of a triangle with area less than
   AREA2. Both parts must be true for the LIC to be true. The condition is not
 met when NUMPOINTS < 5. 0 ≤ AREA2
 *
 * @return true
 * @return false
 */

bool Decide::Lic14() {
  if (NUMPOINTS < 5)
    return false;
  std::vector<COORDINATE> a;
  // conditions can be fullfilled by multiple different points in the array
  bool area1_condition = false;
  bool area2_condition = false;

  for (int i = 0; i < NUMPOINTS - 2 - PARAMETERS.E_PTS - PARAMETERS.F_PTS;
       i++) {
    a.clear();
    a.push_back(COORDINATES[i]);
    a.push_back(COORDINATES[i + PARAMETERS.E_PTS + 1]);
    a.push_back(COORDINATES[i + PARAMETERS.E_PTS + PARAMETERS.F_PTS + 2]);
    double area = fabs(a[0].x * a[1].y + a[1].x * a[2].y + a[2].x * a[0].y -
                       a[0].x * a[2].y - a[1].x * a[0].y - a[2].x * a[1].y) /
                  2;

    // check for area condition 1
    if (DOUBLECOMPARE(area, PARAMETERS.AREA1) == GT) {
      area1_condition = true;
    }
    // check for area condition 2
    if (DOUBLECOMPARE(area, PARAMETERS.AREA2) == LT) {
      area2_condition = true;
    }
    // if both have been fullfilled at some point, return true
    if (area1_condition == true && area2_condition == true) {
      return true;
    }
  }
  return false;
}

void Decide::Calc_PUM() {
  for (int x = 0; x < 15; ++x) {
    for (int y = 0; y < 15; ++y) {
      if (x == y) {
        PUM[y][x] = true;
        continue;
      }

      switch (LCM[y][x]) {
      case ANDD:
        PUM[y][x] = CMV[y] && CMV[x];
        break;

      case ORR:
        PUM[y][x] = CMV[y] || CMV[x];
        break;

      default: // NOTUSED
        PUM[y][x] = true;
        break;
      }
    }
  }
}

void Decide::Calc_FUV() {
  bool a;
  for (int j = 0; j < 15; j++) {
    a = PUM[0][j];
    for (int i = 1; i < 15; i++) {
      a &= PUM[i][j];
    }
    FUV[j] = (!PUV[j]) || a;
  }
};

void Decide::decide() {
  Calc_CMV();
  Calc_PUM();
  Calc_FUV();
  Calc_LAUNCH();
  if (LAUNCH) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

void Decide::Calc_LAUNCH() {
  LAUNCH = true;
  for (int i = 0; i < 15; ++i) {
    LAUNCH = LAUNCH && FUV[i];
  }
}
