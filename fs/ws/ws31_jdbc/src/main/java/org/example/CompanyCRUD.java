/************************************************
 * Title: Crud for Company table operations   *
 * Developer: Or Beruven                        *
 * Reviewer: Nir                                *
 * Date: 05.09.2023                             *
 ************************************************/

package org.example;

import java.sql.*;

public class CompanyCRUD {
    private final Connection connection;

    private static final String updateSQLFirstPart = "update Company set ";
    private static final String updateSQLSecondPart = " = ? where cid = ?";


    private PreparedStatement createStatement;
    private PreparedStatement readStatement;
    private PreparedStatement deleteStatement;

    public CompanyCRUD(Connection connection) {
        this.connection = connection;
        try {
            initStatements();
        } catch (SQLException e) {
            handelException(e);
        }
    }

    public CompanyCRUD(String url) throws SQLException {
        this.connection = DriverManager.getConnection(url);
        try {
            initStatements();
        } catch (SQLException e) {
            handelException(e);
        }
    }

    public int createCompany(String name, String location, Date establish_date) {
        int companyID = 0;
        try {
            createStatement.setString(1, name);
            createStatement.setString(2, location);
            createStatement.setDate(3, establish_date);

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

    public void readCompany(int cid) {
        try {
            readStatement.setInt(1, cid);

            ResultSet resultSet = readStatement.executeQuery();

            while (resultSet.next()) {
                int id = resultSet.getInt("cid");
                String name = resultSet.getString("name");
                String location = resultSet.getString("location");
                Date establish_date = resultSet.getDate("establish_date");

                System.out.println("-------------------------------------------");
                System.out.println(id + " | " + name + " | " + location + " | " + establish_date.toString());
            }

        } catch (SQLException e) {
            handelException(e);
        }
    }

    public boolean updateCompany(int cid, String column, String data) {
        boolean isUpdatedCorrectly = false;
        try (PreparedStatement preparedStatement = createUpdateStatement(cid, column)) {
            preparedStatement.setString(1, data);
            isUpdatedCorrectly = preparedStatement.executeUpdate() != 0;
        } catch (SQLException e) {
            handelException(e);
        }

        return isUpdatedCorrectly;
    }

    public boolean updateCompany(int cid, String column, Date data) {
        boolean isUpdatedCorrectly = false;
        try (PreparedStatement preparedStatement = createUpdateStatement(cid, column)) {
            preparedStatement.setDate(1, data);
            isUpdatedCorrectly = preparedStatement.executeUpdate() != 0;
        } catch (SQLException e) {
            handelException(e);
        }

        return isUpdatedCorrectly;
    }

    public boolean deleteCompany(int cid) {
        boolean isOneRowDeleted = false;
        try {
            deleteStatement.setInt(1, cid);
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
        createStatement = connection.prepareStatement("insert into Company " +
                        "(name, location, establish_date) values(?, ?, ?)",
                Statement.RETURN_GENERATED_KEYS); //adds the + for readable purposes
        readStatement = connection.prepareStatement("select * from Company where cid = ?");
        deleteStatement = connection.prepareStatement("delete from Company where cid = ?");
    }

    private PreparedStatement createUpdateStatement(int cid, String column) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
                updateSQLFirstPart + column + updateSQLSecondPart);
        preparedStatement.setInt(2, cid);

        return preparedStatement;
    }

    private void handelException(SQLException e) {
        e.printStackTrace(System.err);
        System.err.println("SQLState: " + e.getSQLState());
        System.err.println("Error Code: " + e.getErrorCode());
        System.err.println("Message: " + e.getMessage());
    }
}
