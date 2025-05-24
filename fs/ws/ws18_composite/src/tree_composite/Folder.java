/***************************
 *  Written by : Or
 *  Reviewer : Aviv
 *  Date : 15.07.2023
 *  Composite design pattern, tree implementation
 ***************************/
package tree_composite;

import java.util.ArrayList;
import java.util.List;

public class Folder implements Component{
    private String name = null;
    private String indent = "";
    private List<Component> components = new ArrayList<>();

    Folder(String name) {
        this.name = name;
    }
    @Override
    public void print() {
        System.out.println(ColorsClass.ANSI_BLUE  + this.indent + this.name + '/' + ColorsClass.ANSI_RESET);
        for (Component component : this.components) {
            component.incrementIndent(this.indent + "\t");
            component.print();
        }
    }

    @Override
    public void incrementIndent(String indentToAdd) {
        this.indent += indentToAdd;
    }

    public String getName() {
        return name;
    }

    void addComponent(Component component) {
        if (!this.components.contains(component)) {
            this.components.add(component);
        }
    }
}
