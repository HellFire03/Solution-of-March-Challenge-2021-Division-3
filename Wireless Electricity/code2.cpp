import java.util.Arrays;
import java.util.Scanner;

class Codechef {

  static boolean log = false;

  static int N;
  static int M;

  static int maxN = 500001;

  static int[][] towns;
  static int[][] wires;

  static int[][] negativeWires;
  static int[][] positiveWires;
  static int negativeWireIndex;
  static int positiveWireIndex;

  static int[][] moves;
  static int[] POSITIVE = {-1, 0, 0, -1};
  static int[] NEGATIVE = {1000001, 1000000, 1000000, 1000001};
  static int[] LAST_POSITIVE = POSITIVE;;
  static int[] LAST_NEGATIVE = NEGATIVE;
  static StringBuilder sb = new StringBuilder();

  private static long timeStart;

  public static void main(String[] args) throws Exception {
    calculateScanner();
    //      test();
  }

  public static void calculateScanner() throws java.lang.Exception {
    Scanner in = new Scanner(System.in);

    N = in.nextInt();
    timeStart = System.currentTimeMillis();

    M = in.nextInt();
    towns = new int[N][];
    for (int i = 0; i < N; i++) {
      towns[i] = new int[] {in.nextInt(), in.nextInt()};
    }

    wires = new int[M][];
    moves = new int[M][];

    for (int i = 0; i < M; i++) {
      wires[i] = new int[] {in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt()};
      moves[i] = new int[2];
    }
    calculateMoves();
    for (int i = 0; i < M; ) {
      int[] move = moves[i];
      sb.append(move[0]);
      sb.append(' ');
      sb.append(move[1]);
      if (++i < M) {
        sb.append("\n");
      }
    }

    System.out.println(sb);
  }

  static boolean[] dones;
  static int[] closestNegativeWires;
  static int[] closestPositiveWires;

  private static void calculateMoves() {
    dones = new boolean[M];
    negativeWires = new int[M + 1][];
    positiveWires = new int[M + 1][];
    negativeWires[negativeWireIndex++] = NEGATIVE;
    positiveWires[positiveWireIndex++] = POSITIVE;
    closestPositiveWires = new int[M];
    closestNegativeWires = new int[M];

    int m = 0;
    while (m++ < M + 2) {
      if (getTime() > 9900) {
        break;
      }
      int minDistanceNegative = Integer.MAX_VALUE;
      int negative = -1;
      int minDistancePositive = Integer.MAX_VALUE;
      int positive = -1;
      for (int i = 0; i < M; i++) {
        if (!dones[i]) {
          int[] wire = wires[i];
          int distance = distanceSegment(wire, negativeWires);
          closestNegativeWires[i] = segmentIndex;
          if (distance < minDistanceNegative) {
            minDistanceNegative = distance;
            negative = i;
          }
          distance = distanceSegment(wire, positiveWires);
          closestPositiveWires[i] = segmentIndex;

          if (distance < minDistancePositive) {
            minDistancePositive = distance;
            positive = i;
          }
        }
      }
      if (negative == -1 || positive == -1) {
        break;
      }
      if (log) {
        System.err.println("negative " + negative);
        System.err.println("positive " + positive);
      }

      int[] nextPositiveMove = move(wires[positive], positiveWires[closestPositiveWires[positive]]);
      int[] nextPositive = applyMove(wires[positive], nextPositiveMove);
      if (!doIntersect(nextPositive, negativeWires)) {
        moves[positive] = nextPositiveMove;
        positiveWires[positiveWireIndex++] = nextPositive;
        LAST_POSITIVE = nextPositive;
        dones[positive] = true;
      } else {
        if (log) {
          System.err.println(
              "nextPositive " + Arrays.toString(nextPositive) + " intersect with negatives");
        }
      }

      int[] nextNegativeMove = move(wires[negative], negativeWires[closestNegativeWires[negative]]);
      int[] nextNegative = applyMove(wires[negative], nextNegativeMove);

      if (!doIntersect(nextNegative, positiveWires)) {
        moves[negative] = nextNegativeMove;
        negativeWires[negativeWireIndex++] = nextNegative;
        LAST_NEGATIVE = nextNegative;
        dones[negative] = true;
      } else {
        if (log) {
          System.err.println(
              "nextNegative " + Arrays.toString(nextNegative) + " intersect with positives");
        }
      }

      //      moves[negative] = move(wires[negative], LAST_NEGATIVE);
      //      dones[positive] = true;
      //      dones[negative] = true;
      //
      //      LAST_POSITIVE = applyMove(wires[positive], moves[positive]);
      //      LAST_NEGATIVE = applyMove(wires[negative], moves[negative]);
      //
      //      negativeWires[negativeWireIndex++] = LAST_NEGATIVE;
      //      positiveWires[positiveWireIndex++] = LAST_POSITIVE;

      if (log) {
        System.err.println("LAST_POSITIVE " + Arrays.toString(LAST_POSITIVE));
        System.err.println("LAST_NEGATIVE " + Arrays.toString(LAST_NEGATIVE));
        for (int[] move : moves) {
          System.err.println(Arrays.toString(move));
        }
      }
    }
    //    for (int i = 0; i < dones.length; i++) {
    //      if (!dones[i]) {
    //        if (doIntersect(wires[i], positiveWires) && doIntersect(wires[i], negativeWires[i])) {
    //          throw new IllegalStateException();
    //        }
    //      }
    //
    //    }
  }

  static int[][] possibles = {
    {0, 1, 0, 1},
    {0, 1, 2, 3},
    {2, 3, 0, 1},
    {2, 3, 2, 3}
  };

  private static int[] applyMove(int[] segment, int[] move) {
    return new int[] {
      segment[0] + move[0], segment[1] + move[1], segment[2] + move[0], segment[3] + move[1]
    };
  }

  private static boolean doIntersect(int[] segment, int[][] segments) {
    for (int[] seg : segments) {
      if (seg == null) {
        break;
      }
      if (doIntersect(segment, seg)) {
        return true;
      }
    }
    return false;
  }

  private static int[] move(int[] segment, int[][] segments) {
    int minDistance = Integer.MAX_VALUE;
    int[] target = null;
    for (int[] seg : segments) {
      if (seg == null) {
        break;
      }
      int distance = distanceSegment(segment, seg);
      if (minDistance > distance) {
        minDistance = distance;
        target = seg;
      }
    }
    return move(segment, target);
  }

  private static int[] move(int[] segment1, int[] segment2) {
    int minDistance = Integer.MAX_VALUE;
    int minIndex = 0;
    for (int i = 0; i < possibles.length; i++) {
      int[] possible = possibles[i];
      int tmpDistance =
          distance(
              segment1[possible[0]],
              segment1[possible[1]],
              segment2[possible[2]],
              segment2[possible[3]]);
      if (tmpDistance < minDistance) {
        minDistance = tmpDistance;
        minIndex = i;
      }
    }

    int[] possible = possibles[minIndex];
    int[] move =
        new int[] {
          segment2[possible[2]] - segment1[possible[0]],
          segment2[possible[3]] - segment1[possible[1]]
        };
    return move;
  }

  static int segmentIndex = 0;

  private static int distanceSegment(int[] segment, int[][] segments) {
    int minDistance = Integer.MAX_VALUE;
    int i = 0;
    segmentIndex = 0;
    for (int[] seg : segments) {
      if (seg == null) {
        break;
      }
      int distance = distanceSegment(segment, seg);
      if (minDistance > distance) {
        minDistance = distance;
        segmentIndex = i;
      }
      i++;
    }
    return minDistance;
  }

  private static int distanceSegment(int[] segment, int[] segment2) {
    return Math.min(
        distanceSegment(segment[0], segment[1], segment2),
        distanceSegment(segment[2], segment[3], segment2));
  }

  private static int distanceSegment(int x1, int y1, int[] segment) {
    return Math.min(
        distance(x1, y1, segment[0], segment[1]), distance(x1, y1, segment[2], segment[3]));
  }

  private static int distance(int x1, int y1, int x2, int y2) {
    return Math.abs(x1 - x2) + Math.abs(y1 - y2);
  }

  static int[] a = new int[2];
  static int[] b = new int[2];

  static int[] c = new int[2];

  static int[] d = new int[2];

  private static boolean doIntersect(int[] segment, int[] seg) {
    //    a[0] = segment[0];
    //    a[1] = segment[1];
    //    b[0] = segment[2];
    //    b[1] = segment[3];
    //
    //    c[0] = seg[0];
    //    c[1] = seg[1];
    //    d[0] = seg[2];
    //    d[1] = seg[3];
    //    return doIntersect(a, b, c, d);
    return doIntersect(
        segment[0],
        segment[1],
        segment[2],
        segment[3],
        seg[0],
        seg[1],
        seg[2],
        seg[3]);
  }

  static boolean doIntersect(
      int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y) {
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;
    s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;
    s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
      // Collision detected

      return true;
    }

    return false; // No collision
  }
  // Given three colinear points p, q, r, the function checks if
  // point q lies on line segment 'pr'
  static boolean onSegment(int[] p, int[] q, int[] r) {
    if (q[0] <= Math.max(p[0], r[0])
        && q[0] >= Math.min(p[0], r[0])
        && q[1] <= Math.max(p[1], r[1])
        && q[1] >= Math.min(p[1], r[1])) return true;

    return false;
  }

  // To find orientation of ordered triplet (p, q, r).
  // The function returns following values
  // 0 --> p, q and r are colinear
  // 1 --> Clockwise
  // 2 --> Counterclockwise
  static int orientation(int[] p, int[] q, int[] r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);

    if (val == 0) return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
  }

  // The main function that returns true if line segment 'p1q1'
  // and 'p2q2' intersect.
  static boolean doIntersect(int[] p1, int[] q1, int[] p2, int[] q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
  }

  public static long getTime() {
    return System.currentTimeMillis() - timeStart;
  }
}
