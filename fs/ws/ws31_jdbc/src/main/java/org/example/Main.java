package org.example;

import java.sql.*;
import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        try (Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/CRUD",
                "OrBeru", "1234")) {
            System.out.println(con.getTransactionIsolation() + " = my isolation level");
            System.out.println(Connection.TRANSACTION_REPEATABLE_READ + " = TRANSACTION_REPEATABLE_READ");
            testProduct(con);
            testCompany(con);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private static void testProduct(Connection con) {
        ProductCRUD productCRUD = new ProductCRUD(con);
        int pid = productCRUD.createProduct("Or", "melech",
                Date.valueOf(LocalDate.of(1999, 12, 27)));

        productCRUD.readProduct(pid);

        if (!productCRUD.updateProduct(pid, "name", "Dor")) {
            throw new RuntimeException();
        }
        productCRUD.readProduct(pid);

        if (!productCRUD.updateProduct(pid, "date", Date.valueOf(LocalDate.now()))) {
            throw new RuntimeException();
        }
        productCRUD.readProduct(pid);

        if (!productCRUD.deleteProduct(pid)) {
            throw new RuntimeException();
        }
    }

    private static void testCompany(Connection con) {
        CompanyCRUD companyCRUD = new CompanyCRUD(con);
        int cid = companyCRUD.createCompany("Tornado", "Tel-Aviv",
                Date.valueOf(LocalDate.of(1987, 1, 21)));

        companyCRUD.readCompany(cid);

        if (!companyCRUD.updateCompany(cid, "location", "New-York")) {
            throw new RuntimeException();
        }
        companyCRUD.readCompany(cid);

        if (!companyCRUD.updateCompany(cid, "establish_date", Date.valueOf(LocalDate.now()))) {
            throw new RuntimeException();
        }
        companyCRUD.readCompany(cid);

        if (!companyCRUD.deleteCompany(cid)) {
            throw new RuntimeException();
        }

        companyCRUD.closeCRUD();
    }
}