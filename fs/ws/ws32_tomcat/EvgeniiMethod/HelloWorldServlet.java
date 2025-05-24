import java.io.IOException;
   import javax.servlet.ServletException;
   import javax.servlet.annotation.WebServlet;
   import javax.servlet.http.HttpServlet;
   import javax.servlet.http.HttpServletRequest;
   import javax.servlet.http.HttpServletResponse;

   @WebServlet("/HelloWorld")
   public class HelloWorldServlet extends HttpServlet {
       protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
           // Retrieve the 'name' parameter from the URL
           String name = request.getParameter("name");

           // Set the content type and write the response
           response.setContentType("text/html");
           response.getWriter().println("Hello, " + name);
       }
   }
