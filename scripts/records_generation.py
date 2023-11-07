import json
import sys

# Function to create multiple records based on the initial record
def generate_records(initial_record, num_records):
    generated_records = {}

    for i in range(1, num_records + 1):
        new_record = initial_record.copy()  # Create a copy of the initial record
        new_record[f"RouteID_{i:02}"] = new_record.pop("RouteID_01")  # Change the key name
        generated_records.update(new_record)  # Add the new record to the generated set

    return generated_records

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script_name.py <path_to_initial_record> <num_records>")
        sys.exit(1)

    initial_record_path = sys.argv[1]
    num_records = int(sys.argv[2])

    # Read the initial JSON record from the file
    try:
        with open(initial_record_path, 'r') as file:
            initial_record = json.load(file)
    except FileNotFoundError:
        print("File not found. Please provide a valid path to the initial record.")
        sys.exit(1)

    # Generate the records
    generated_data = generate_records(initial_record, num_records)

    # Write the generated records to a JSON file
    output_file = "generated_records_{num_records}.json".format(num_records=num_records)
    with open(output_file, "w") as file:
        json.dump(generated_data, file, indent=4)

    print(f"Generated {num_records} records in '{output_file}'.")
