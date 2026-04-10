// header Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// value Directives
#define MAX_PATIENTS 100
#define MAX_BEDS 10
#define MAX_MAPPINGS 100
#define MAX_MEDICINES 100

// Structure for patient information
typedef struct 
{
    char name[100];
    int age;
    char gender[10];
    char disease[100];
    char doctor[100];
    int duration;
    int bed_number;
    char ward_type[20];
    int admitted;
    char medicines[10][100];
    int medicine_qty[10];
    int medicine_count;
    int medicine_cost;
} Patient;

// Structure for disease to doctor mapping
typedef struct {
    char disease[100];
    char doctor[100];
    int duration;
} DiseaseMapping;

// Structure for medicine mapping
typedef struct {
    char name[100];
    int price;
} MedicineMapping;

// Initialisation
Patient patients[MAX_PATIENTS];
int patient_count = 0;

int general_beds[MAX_BEDS] = {0};
int semi_special_beds[MAX_BEDS] = {0};
int special_beds[MAX_BEDS] = {0};

//Database
DiseaseMapping mappings[MAX_MAPPINGS] = 
{
    {"Ovarian Cyst", "Dr. Shruthi", 30},
    {"PCOS", "Dr. Shruthi", 45},
    {"Menstrual Irregularities", "Dr. Shruthi", 30},
    {"Heart Attack", "Dr. Rajesh", 60},
    {"High Blood Pressure", "Dr. Rajesh", 30},
    {"Eczema", "Dr. Priya", 15},
    {"Psoriasis", "Dr. Priya", 30},
    {"Arthritis", "Dr. Ankit", 60},
    {"Fractured Bone", "Dr. Ankit", 45},
    {"Stroke", "Dr. Suresh", 90},
    {"Migraine", "Dr. Suresh", 10},
    {"Pneumonia", "Dr. Arvind", 30},
    {"Asthma", "Dr. Arvind", 20},
    {"Pediatric Fever", "Dr. Anjali", 7},
    {"Vaccination", "Dr. Anjali", 1},
    {"Ear Infection", "Dr. Vivek", 7},
    {"Tinnitus", "Dr. Vivek", 30},
    {"Depression", "Dr. Kiran", 60},
    {"Anxiety", "Dr. Kiran", 30},
    {"Cavity", "Dr. Neha", 15},
    {"Gingivitis", "Dr. Neha", 10},
    {"Diabetes", "Dr. Ravi", 30},
    {"Thyroid Disorder", "Dr. Ravi", 45},
    {"Liver Disease", "Dr. Shweta", 60},
    {"Ulcer", "Dr. Shweta", 30},
    {"Urinary Tract Infection", "Dr. Arun", 15},
    {"Kidney Stones", "Dr. Arun", 45},
    {"Cataract", "Dr. Deepa", 30},
    {"Glaucoma", "Dr. Deepa", 60},
    {"Lung Cancer", "Dr. Arvind", 120},
    {"Chronic Bronchitis", "Dr. Arvind", 90},
    {"Lupus", "Dr. Seema", 180},
    {"Osteoarthritis", "Dr. Seema", 120}
};
int mapping_count = 33;

MedicineMapping medicines[MAX_MEDICINES] = 
{
    {"Paracetamol", 20},
    {"Dolo", 15},
    {"Azithromycin", 50},
    {"Ivermectin", 30},
    {"Aspirin", 25},
    {"Ibuprofen", 18},
    {"Amoxicillin", 35},
    {"Ciprofloxacin", 40},
    {"Cetirizine", 10},
    {"Loratadine", 12},
    {"Metformin", 60},
    {"Losartan", 55},
    {"Alprazolam", 45},
    {"Diazepam", 40},
    {"Clopidogrel", 70},
    {"Hydrochlorothiazide", 20},
    {"Levothyroxine", 80},
    {"Omeprazole", 25},
    {"Simvastatin", 50},
    {"Metoprolol", 30},
    {"Dexamethasone", 60},
    {"Prednisolone", 55},
    {"Paroxetine", 40},
    {"Fluoxetine", 45},
};
int medicine_count = 24;

// Printing wards
void view_all_wards() 
{
    printf("\nGeneral Ward Beds:\n");
    for (int i = 0; i < MAX_BEDS; i++)
        printf("Bed %d: %s\n", i + 1, general_beds[i] ? "Occupied" : "Available");

    printf("\nSemi-Special Ward Beds:\n");
    for (int i = 0; i < MAX_BEDS; i++)
        printf("Bed %d: %s\n", i + 1, semi_special_beds[i] ? "Occupied" : "Available");

    printf("\nSpecial Ward Beds:\n");
    for (int i = 0; i < MAX_BEDS; i++)
        printf("Bed %d: %s\n", i + 1, special_beds[i] ? "Occupied" : "Available");
}

int assign_bed(char ward_type[], int *bed_number) 
{
    int *ward;
    if (strcmp(ward_type, "General") == 0)
        ward = general_beds;
    else if (strcmp(ward_type, "Semi-Special") == 0)
        ward = semi_special_beds;
    else if (strcmp(ward_type, "Special") == 0)
        ward = special_beds;
    else
        return 0;

    for (int i = 0; i < MAX_BEDS; i++) {
        if (ward[i] == 0) 
        {
            ward[i] = 1;
            *bed_number = i + 1;
            return 1;
        }
    }
    return 0;
}

void admit_patient() {
    if (patient_count >= MAX_PATIENTS) {
        printf("Max patient limit reached!\n");
        return;
    }

    Patient p;
    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    strtok(p.name, "\n");

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    int valid = 0;
    while (!valid) {
        printf("Enter Gender (Male/Female/Other): ");
        fgets(p.gender, sizeof(p.gender), stdin);
        strtok(p.gender, "\n");
        if (strcmp(p.gender, "Male") == 0 || strcmp(p.gender, "Female") == 0 || strcmp(p.gender, "Other") == 0)
            valid = 1;
        else
            printf("Invalid gender. Please try again.\n");
    }

    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    strtok(p.disease, "\n");

    int found = 0;
    for (int i = 0; i < mapping_count; i++) {
        if (strcmp(mappings[i].disease, p.disease) == 0) {
            strcpy(p.doctor, mappings[i].doctor);
            p.duration = mappings[i].duration;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Disease not found in mapping list.\n");
        return;
    }

    printf("Enter Ward Type (General/Semi-Special/Special): ");
    fgets(p.ward_type, sizeof(p.ward_type), stdin);
    strtok(p.ward_type, "\n");

    if (!assign_bed(p.ward_type, &p.bed_number)) {
        printf("No bed available in the selected ward.\n");
        return;
    }

    printf("Select medicines by index from the list below (use * for quantity, enter 'done' to finish):\n");
    for (int i = 0; i < medicine_count; i++) {
        printf("%d. %s -  %d\n", i + 1, medicines[i].name, medicines[i].price);
    }
    p.medicine_cost = 0;
    p.medicine_count = 0;
    while (1) {
        char input[100];
        printf("Enter medicine index (e.g., 1*2 or 3): ");
        fgets(input, sizeof(input), stdin);
        strtok(input, "\n");
        if (strcmp(input, "done") == 0) break;

        int index, qty = 1;
        char *star = strchr(input, '*');
        if (star) {
            *star = '\0';
            index = atoi(input);
            qty = atoi(star + 1);
        } else {
            index = atoi(input);
        }

        if (index < 1 || index > medicine_count || qty < 1) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        strcpy(p.medicines[p.medicine_count], medicines[index - 1].name);
        p.medicine_qty[p.medicine_count] = qty;
        p.medicine_cost += medicines[index - 1].price * qty;
        p.medicine_count++;
    }

    p.admitted = 1;
    patients[patient_count++] = p;

    printf("Patient admitted successfully to bed %d in %s ward.\n", p.bed_number, p.ward_type);
}

void discharge_patient() {
    char name[100];
    printf("Enter Patient Name to Discharge: ");
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");

    for (int i = 0; i < patient_count; i++) {
        if (patients[i].admitted && strcmp(patients[i].name, name) == 0) {
            printf("Discharging %s...\n", patients[i].name);
            printf("Doctor: %s\n", patients[i].doctor);
            printf("Stay Duration: %d days\n", patients[i].duration);

            int ward_cost_per_day =
                strcmp(patients[i].ward_type, "General") == 0 ? 1000 :
                strcmp(patients[i].ward_type, "Semi-Special") == 0 ? 2000 : 3000;
            int stay_cost = patients[i].duration * ward_cost_per_day;

            printf("Medicines used:\n");
            for (int j = 0; j < patients[i].medicine_count; j++) {
                printf("- %s x%d\n", patients[i].medicines[j], patients[i].medicine_qty[j]);
            }
            printf("Medicine Cost:  %d\n", patients[i].medicine_cost);
            printf("Ward Cost:  %d\n", stay_cost);
            printf("Total Bill:  %d\n", stay_cost + patients[i].medicine_cost);

            int bed_index = patients[i].bed_number - 1;
            if (strcmp(patients[i].ward_type, "General") == 0)
                general_beds[bed_index] = 0;
            else if (strcmp(patients[i].ward_type, "Semi-Special") == 0)
                semi_special_beds[bed_index] = 0;
            else
                special_beds[bed_index] = 0;

            patients[i].admitted = 0;
            return;
        }
    }
    printf("Patient not found or already discharged.\n");
}

void list_patients() {
    printf("\n--- Admitted Patients ---\n");
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].admitted) {
            printf("\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\nRecovery Time: %d days\nWard: %s\nBed No: %d\n",
                   patients[i].name, patients[i].age, patients[i].gender,
                   patients[i].disease, patients[i].doctor, patients[i].duration,
                   patients[i].ward_type, patients[i].bed_number);

            printf("Medicines:\n");
            for (int j = 0; j < patients[i].medicine_count; j++) {
                printf("- %s x%d\n", patients[i].medicines[j], patients[i].medicine_qty[j]);
            }

            int ward_cost_per_day =
                strcmp(patients[i].ward_type, "General") == 0 ? 1000 :
                strcmp(patients[i].ward_type, "Semi-Special") == 0 ? 2000 : 3000;
            int stay_cost = patients[i].duration * ward_cost_per_day;            int total_bill = stay_cost + patients[i].medicine_cost;

            printf("Medicine Cost:  %d\nWard Cost:  %d\nTotal Bill:  %d\n",
                   patients[i].medicine_cost, stay_cost, total_bill);
            printf("Patient will be discharged in %d days \n",patients[i].duration+10);
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Hospital Management Dashboard ---\n");
        printf("1. Admit Patient\n");
        printf("2. Discharge Patient\n");
        printf("3. View Ward Status\n");
        printf("4. List Admitted Patients\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                admit_patient();
                break;
            case 2:
                discharge_patient();
                break;
            case 3:
                view_all_wards();
                break;
            case 4:
                list_patients();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}