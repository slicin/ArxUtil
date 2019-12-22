//#include <iostream>
//#include <cmath>
//
//int main()
//{
//	std::cout << " ===== Normalized Forward Vector Calculator =====";
//
//	float pitch;
//	float yaw;
//	float x, y, z, sum;
//	float pi = 3.14;
//
//	bool calculating = true;
//	while (calculating)
//	{
//		// Collect Rotations
//		std::cout << "\n\nEnter Pitch (0-359.999): ";
//		std::cin >> pitch;
//		std::cout << "Enter Yaw (0-359.999): ";
//		std::cin >> yaw;
//
//		// Convert degrees to radians
//		pitch = pitch * (pi / 180);
//		yaw = yaw * (pi / 180);
//
//		// Calculate forward vector using rotations
//		// The coordinate system of Arx Fatalis is rotated 180 degrees
//		// on the Z axis, which maintains normal behavior on the X and Z
//		// axes, but flips the behavior of Y. This is indicated because
//		// decreasing player's Y Position moves them up, yet walking forward
//		// with zero yaw increases Z Position as usual. Another strange
//		// side effect of this is that Yaw appears to count counterclockwise.
//		x = -(cos(pitch) * sin(yaw)); // Negative to compensate for reversed yaw
//		y = sin(pitch);
//		z = cos(pitch) * cos(yaw);
//
//		std::cout << "Forward Vector: " <<
//			"(" << x << ", " << y << ", " << z << " )";
//
//		// Normalize forward vector to absolute sum 1
//		// Divide each number by the sum of all absolute numbers
//		sum = abs(x) + abs(y) + abs(z);
//		x = x / sum;
//		y = y / sum;
//		z = z / sum;
//
//		std::cout << "\nNormalized: " <<
//			"(" << x << ", " << y << ", " << z << " )";
//	}
//
//	std::cout << "\n\n";
//	system("pause");
//
//	return 0;
//}