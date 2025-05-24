/***************************
 *  Written by : Or
 *  Reviewer : Aviv
 *  Date : 15.07.2023
 *  Composite design pattern, tree implementation
 ***************************/
package tree_composite;
import java.io.File;

public class Tree {
    private Component root = null;
    private File file = null;
    public Tree(String path) {
        this.file = new File(path);
        if (!file.exists()) {
            throw new RuntimeException("Invalid path sent to Tree");
        }

        if (this.file.isDirectory()) {
            File[] files = file.listFiles();
            this.root = new Folder(file.getName());
            if (null != files) {
                recursiveInit(files, (Folder) this.root);
            }
        }
        else {
            this.root = new FileComponent(file.getName());
        }
    }

    private void recursiveInit(File[] files, Folder targetFolder) {
        for (File f : files) {
            if (f.isDirectory()) {
                Folder newFolder = new Folder(f.getName());
                targetFolder.addComponent(newFolder);

                File[] subFiles = f.listFiles();
                if (null != subFiles) {
                    recursiveInit(subFiles, newFolder);
                }
            } else {
              FileComponent newFile = new FileComponent(f.getName());
              targetFolder.addComponent(newFile);
            }
        }
    }
    public void print() {
        root.print();
    }
}
