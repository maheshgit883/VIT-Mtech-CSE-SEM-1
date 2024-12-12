import java.io.File;
import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;


public class XSDValidator {
    public static void main(String[] args) {
        String xsdPath = "C:/Users/Jagta/OneDrive/Desktop/VIT SEM1/DBMS/LAB ASSIGNMENTS/schema.xsd"; 

        String[] xmlPaths = {
            "C:/Users/Jagta/OneDrive/Desktop/VIT SEM1/DBMS/LAB ASSIGNMENTS/department.xml",
            "C:/Users/Jagta/OneDrive/Desktop/VIT SEM1/DBMS/LAB ASSIGNMENTS/employee.xml",
            "C:/Users/Jagta/OneDrive/Desktop/VIT SEM1/DBMS/LAB ASSIGNMENTS/project.xml"
        };
        for (String xmlPath : xmlPaths) {
            validateXMLSchema(xsdPath, xmlPath);
        }
    }


    public static void validateXMLSchema(String xsdPath, String xmlPath) {
        try {
            SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(new File(xsdPath));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(new File(xmlPath)));
            System.out.println(xmlPath + " is valid against " + xsdPath);
        } catch (Exception e) {
            System.out.println(xmlPath + " is not valid. Error: " + e.getMessage());
        }
    }
}
