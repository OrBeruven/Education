/***************************
 *  Written by : Or
 *  Reviewer : Aviv
 *  Date : 15.07.2023
 *  Composite design pattern, tree implementation
 ***************************/
package tree_composite;

public class FileComponent implements Component {
    String name = null;
    private String indent = "";
    FileComponent(String name) {
        this.name = name;
    }
    @Override
    public void print() {
        System.out.println(ColorsClass.ANSI_RED + this.indent + this.getName() + ColorsClass.ANSI_RESET);
    }

    @Override
    public void incrementIndent(String indentToAdd) {
        this.indent += indentToAdd;
    }

    private String getName() {
        return this.name;
    }
}
