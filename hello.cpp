#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to calculate the initial angle between the hour and minute hands
double get_initial_angle(int hour, int minute) {
    // Minute hand moves 6 degrees per minute
    double minute_angle = 6 * minute;
    // Hour hand moves 30 degrees per hour + 0.5 degrees per minute
    double hour_angle = 30 * (hour % 12) + 0.5 * minute;
    
    // Find the absolute difference between the angles
    double angle = fabs(hour_angle - minute_angle);
    
    // Return the smaller of the interior and exterior angle
    return min(angle, 360 - angle);
}

// Function to calculate the cost for a given query to reach the target angle
int get_minimum_cost(double initial_angle, int target_angle, int A, int B, int X, int Y) {
    // Calculate the angle difference between the current and target angles
    double angle_diff = fabs(initial_angle - target_angle);
    
    // If the angle is greater than 180 degrees, use the exterior angle
    if (angle_diff > 180) {
        angle_diff = 360 - angle_diff;
    }
    
    // Costs for minute hand movement (clockwise and anti-clockwise)
    int cost_minute_clockwise = (int)(angle_diff * Y * A);
    int cost_minute_anticlockwise = (int)((360 - angle_diff) * Y * B);
    
    // Costs for hour hand movement (clockwise and anti-clockwise)
    int cost_hour_clockwise = (int)(angle_diff * X * A);
    int cost_hour_anticlockwise = (int)((360 - angle_diff) * X * B);
    
    // Return the minimum cost among all the options
    return min({cost_minute_clockwise, cost_minute_anticlockwise, cost_hour_clockwise, cost_hour_anticlockwise});
}

int main() {
    int hour, minute, Q;
    char colon;
    
    // Input: Read the initial time (hour and minute)
    cin >> hour >> colon >> minute;
    
    // Input: Read the number of queries
    cin >> Q;
    
    // Input: Read the costs A, B, X, Y
    int A, B, X, Y;
    cin >> A >> B >> X >> Y;
    
    // Get the initial angle between the hands of the clock
    double initial_angle = get_initial_angle(hour, minute);
    
    // Total cost accumulator
    int total_cost = 0;
    
    // Process each query
    for (int i = 0; i < Q; ++i) {
        int target_angle;
        cin >> target_angle;
        
        // Calculate and add the minimum cost for this query
        total_cost += get_minimum_cost(initial_angle, target_angle, A, B, X, Y);
        
        // After processing the query, update the current angle to the target angle
        initial_angle = target_angle;
    }
    
    // Output the total minimum cost
    cout << total_cost << endl;
    
    return 0;
}
