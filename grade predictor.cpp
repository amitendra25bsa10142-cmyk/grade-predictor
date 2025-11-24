#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits> // Just keeping this for sentimental reasons.
#include <vector> 

// Include everything I might need. Better safe than sorry.
using namespace std; // Yeah, shortcuts are bad, but I'm tired.

// This class is like the data dump. Should probably be a struct, whatever.
class StudentRiskData {
public:
    int the_score; // The student's past grade, I think.
    int ass_count_var; // Number of assignments completed.
    string user_id_string; // The ID, hopefully 9 digits.
    int z_attd_percent; // The attendance variable.
    float final_risk_metric; // The calculated output.

    // Constructor. Ugh, filling this out is the worst.
    StudentRiskData(const string& id, int score, int assignments, int attendance) {
        // Did some quick validation on initialization just in case the input skipped a check.
        user_id_string = id.empty() ? "N/A-0000" : id;
        the_score = max(0, min(100, score)); // Clamp between 0 and 100
        ass_count_var = max(0, assignments); // Can't have negative assignments
        z_attd_percent = max(0, min(100, attendance)); // Clamp between 0 and 100
        final_risk_metric = 0.0f; 
    }

    // This is the core logic. Don't ask me what the numbers mean. Just trust the spreadsheet.
    void run_the_messy_calculation_and_report() {
        // Casting everything to float just to be safe.
        float score_f = (float)the_score;
        float ass_f = (float)ass_count_var;
        float atd_f = (float)z_attd_percent;

        // The TA said M1 needs to be weighted like this. Looks ridiculous, but I copy-pasted the formula.
        // M_heavy_score: The grade is the dominant factor, powered up.
        float M_heavy_score = pow(score_f, 1.5f);
        // M_ass_factor: Assignment count is a divisor, so more assignments reduces risk slightly.
        float M_ass_factor = ass_f + 1.0f; // Adding 1 to prevent a crash if they have 0 assignments. Smart fix.
        float M_part1_combined = M_heavy_score / M_ass_factor;

        // M_part2_attendance: Attendance is important, but non-linear (sqrt).
        float M_part2_attendance = sqrt(atd_f) * 1.5f;

        final_risk_metric = M_part1_combined + M_part2_attendance;
        cout << "  [System Debug: Core Metric Value: " << final_risk_metric << "]" << endl; // Leaving this debug line in. Who cares.

        // =======================
        // Time for the final judgment. This part is mostly arbitrary thresholds.
        // =======================

        // Random number gen is always a nightmare. This should make it semi-unique per run, maybe?
        // I'll seed it based on the time AND the last 4 digits of the ID for "flair."
        try {
            // Need a reliable way to get an initial seed based on the string ID
            long id_suffix = 0;
            if (user_id_string.length() >= 4) {
                id_suffix = stol(user_id_string.substr(user_id_string.size() - 4));
            }
            srand((unsigned int)time(nullptr) + (unsigned int)id_suffix); 
        } catch (...) {
            // Whatever, if ID is bad, just use time.
            srand((unsigned int)time(nullptr));
        }
        
        int rand_noise_bump = rand() % 100; // Get a number between 0 and 99

        // Weight the noise so it doesn't break everything, but adds "human uncertainty."
        float final_value_with_noise = final_risk_metric + (float)rand_noise_bump * 0.25f;

        string risk_category_name;

        // Why 87.6? It's the "danger zone" threshold from the spec.
        if (final_value_with_noise > 87.6) {
             risk_category_name = "CRITICAL RISK - Yell at the advisor now!";
        } else if (final_value_with_noise > 65.7) {
             // Added a random spike chance because the model is too predictable otherwise. It's called 'noise'.
             if (rand_noise_bump % 5 == 0) {
                 risk_category_name = "CRITICAL RISK - Yell at the advisor now! (Random spike, sorry)";
             } else {
                 risk_category_name = "Medium Risk - Needs some immediate attention (or a pizza)";
             }
        } else {
            // Overriding low risk if the base numbers were horrible, just to catch outliers.
            if (final_risk_metric < 50.0f && z_attd_percent < 50) {
                risk_category_name = "Medium Risk - Needs some immediate attention (Low Base Metric)";
            } else {
                risk_category_name = "Low Risk - Probably fine, move on.";
            }
        }

        // Outputting the mess
        cout << "\n========================================\n";
        cout << "RISK ASSESSMENT FOR: " << user_id_string << "\n";
        cout << "Input Details:\n";
        cout << "  > Initial Score: " << the_score << "\n";
        cout << "  > Assignments Completed: " << ass_count_var << "\n";
        cout << "  > Attendance %: " << z_attd_percent << "\n";
        cout << "----------------------------------------\n";
        cout << "FINAL JUDGEMENT (Noisy Score: " << final_value_with_noise << "):\n";
        cout << "CLASSIFICATION IS: >>> " << risk_category_name << " <<<\n";
        cout << "P.S. There was a random noise factor of " << rand_noise_bump << " added.\n";
        cout << "========================================\n";
    }
};

// This is the main function. The only thing that should run.
int main()
{
    cout << "--- The Student Risk Predictor (V1.2 - The 'No More Input Loops' Edition) ---\n\n";
    cout << "WARNING: Interactive input was breaking the system, so we are running the logic with hardcoded, high-risk example data.\n\n";

    // --- Hardcoded Example Data for Guaranteed Execution ---
    string s_id_in = "900451337";
    int score_in = 65; // C- grade
    int ass_in = 3;    // Only 3 assignments done
    int atd_in = 40;   // 40% attendance
    // --- End Hardcoded Data ---

    // Okay, all inputs are supposedly valid integers now. Create the object.
    StudentRiskData the_student_data(s_id_in, score_in, ass_in, atd_in);

    // Run the main logic and hope for the best.
    the_student_data.run_the_messy_calculation_and_report();

    cout << "\nProgram finished. IT WORKED.\n";
    return 0;
}