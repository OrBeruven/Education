/************************************************
 * Title: Crud for Product table operations   *
 * Developer: Or Beruven                        *
 * Reviewer: Nir                                *
 * Date: 05.09.2023                             *
 ************************************************/
package org.example;

import java.sql.*;

public class ProductCRUD {
    private final Connection connection;

    private static final String updateSQLFirstPart = "update Product set ";
    private static final String updateSQLSecondPart = " = ? where pid = ?";


    private PreparedStatement createStatement;
    private PreparedStatement readStatement;
    private PreparedStatement deleteStatement;

    public ProductCRUD(Connection connection) {
        this.connection = connection;
        try {
            initStatements();
        } catch (SQLException e) {
            handelException(e);
        }
    }

    public ProductCRUD(String url) throws SQLException {
        this.connection = DriverManager.getConnection(url);
        try {
            initStatements();
        } catch (SQLException e) {
            handelException(e);
        }
    }

    public int createProduct(String name, String model, Date date) {
        int companyID = 0;
        try {
            createStatement.setString(1, name);
            createStatement.setString(2, model);
            createStatement.setDate(3, date);

            int rowsInserted = createStatement.executeUpdate();
            if (1 != rowsInserted) {
                throw new RuntimeException();
            }

            ResultSet key = createStatement.getGeneratedKeys();

            if (!key.next()) {
                throw new RuntimeException();
            } else {
                companyID = key.getInt(1);
            }

        } catch (SQLException e) {
            handelException(e);
        }

        return companyID;
    }

    public void readProduct(int pid) {
        try {
            readStatement.setInt(1, pid);

            ResultSet resultSet = readStatement.executeQuery();

            while (resultSet.next()) {
                int id = resultSet.getInt("pid");
                String name = resultSet.getString("name");
                String model = resultSet.getString("model");
                Date date = resultSet.getDate("date");

                System.out.println("-------------------------------------------");
                System.out.println(id + " | " + name + " | " + model + " | " + date.toString());
            }

        } catch (SQLException e) {
            handelException(e);
        }
    }

    public boolean updateProduct(int pid, String column, String data) {
        boolean isUpdatedCorrectly = false;
        try (PreparedStatement preparedStatement = createUpdateStatement(pid, column)) {
            preparedStatement.setString(1, data);
            isUpdatedCorrectly = preparedStatement.executeUpdate() != 0;
        } catch (SQLException e) {
            handelException(e);
        }

        return isUpdatedCorrectly;
    }

    public boolean updateProduct(int pid, String column, Date data) {
        boolean isUpdatedCorrectly = false;
        try (PreparedStatement preparedStatement = createUpdateStatement(pid, column)) {
            preparedStatement.setDate(1, data);
            isUpdatedCorrectly = preparedStatement.executeUpdate() != 0;
        } catch (SQLException e) {
            handelException(e);
        }

        return isUpdatedCorrectly;
    }

    public boolean deleteProduct(int pid) {
        boolean isOneRowDeleted = false;
        try {
            deleteStatement.setInt(1, pid);
            isOneRowDeleted = deleteStatement.executeUpdate() == 1;
        } catch (SQLException e) {
            handelException(e);
        }

        return isOneRowDeleted;
    }

    public void closeCRUD() {
        try {
            connection.close();
            createStatement.close();
            readStatement.close();
            deleteStatement.close();
        } catch (SQLException e) {
            handelException(e);
        }
    }

    private void initStatements() throws SQLException {
        createStatement = connection.prepareStatement("insert into Product " +
                        "(name, model, date) values(?, ?, ?)",
                Statement.RETURN_GENERATED_KEYS); //adds the + for readable purposes
        readStatement = connection.prepareStatement("select * from Product where pid = ?");
        deleteStatement = connection.prepareStatement("delete from Product where pid = ?");
    }

    private PreparedStatement createUpdateStatement(int pid, String column) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
                updateSQLFirstPart + column + updateSQLSecondPart);
        preparedStatement.setInt(2, pid);

        return preparedStatement;
    }

    private void handelException(SQLException e) {
        e.printStackTrace(System.err);
        System.err.println("SQLState: " + e.getSQLState());
        System.err.println("Error Code: " + e.getErrorCode());
        System.err.println("Message: " + e.getMessage());
    }
}

