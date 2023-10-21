import sqlite3

# Connect to the database

# Create a cursor object
def view_db():
    conn = sqlite3.connect('db.sqlite3')

    cursor = conn.cursor()

    # Perform a SELECT query to fetch data from the 'users' table
    cursor.execute("SELECT * FROM api_product")
    rows = cursor.fetchall()

    # Print the fetched data
    for row in rows:
        print(row)

    # Close the connection
    conn.close()

def update_product_state(product_id:int, new_state:bool):
    # Connect to the database
    conn = sqlite3.connect('db.sqlite3')


    # Create a cursor object
    cursor = conn.cursor()

    # Execute the UPDATE statement
    cursor.execute("UPDATE api_product SET state = ? WHERE id = ?", (new_state, product_id))

    # Commit the changes
    conn.commit()

    # Close the connection
    conn.close()

def get_product_data():
    # Connect to the database
    conn = sqlite3.connect('db.sqlite3')

    # Create a cursor object
    cursor = conn.cursor()

    # Execute the SELECT query to fetch data from the 'api_product' table
    cursor.execute("SELECT * FROM api_product")

    # Fetch all the rows
    rows = cursor.fetchall()

    # Close the connection
    conn.close()

    # Return the fetched data as a list of rows
    return rows

# Example usage: # get_product_data
# product_data_list = get_product_data()
# print(product_data_list)

# Example usage: # update_product_state
# view_db()
# product_id_to_update = 1
# new_state_value = False

# update_product_state(product_id_to_update, new_state_value)
# view_db()



