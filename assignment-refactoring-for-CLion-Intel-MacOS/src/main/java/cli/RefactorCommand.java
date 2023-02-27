package cli;

import picocli.CommandLine;
import picocli.CommandLine.Command;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.Callable;

@Command(
        name = "refactor",
        description = "Refactors the current assignment directory (as downloaded and unzipped from WeBeep, " +
                "e.g. \"A01\") to make it compatible with CLion running on an Intel Mac - the VulkanSDK should have " +
                "been downloaded under /Users/USERNAME/VulkanSDK/1.3.239.0/macOS and the glfw library should have " +
                "been downloaded using homebrew"
)
public class RefactorCommand implements Callable<Integer> {
    private final static String ASSIGNMENT_PLACEHOLDER = "ASSIGNMENT";
    private final static String USERNAME_PLACEHOLDER = "USERNAME";
    private final String currentDirectory;
    private final String currentUser;

    public RefactorCommand() {
        currentDirectory = System.getProperty("user.dir");
        currentUser = System.getProperty("user.name");
    }

    public static void main(String[] args) {
        int exitCode = new CommandLine(new RefactorCommand()).execute(args);
        System.exit(exitCode);
    }

    @Override
    public Integer call() {

        return createCMakeFile();
    }

    private Integer createCMakeFile() {
        System.out.println("Creating CMake file...");
        File cMakeTemplateFile = new File("src/main/resources/CMakeListsTemplate.txt");

        try {
            Scanner fileReader = new Scanner(cMakeTemplateFile);
            StringBuilder stringBuilder = new StringBuilder();
            while (fileReader.hasNextLine()) {
                stringBuilder.append(fileReader.nextLine());
                stringBuilder.append("\n");
            }

            String cMakeTemplateString = stringBuilder.toString();
            cMakeTemplateString = cMakeTemplateString.replaceAll(ASSIGNMENT_PLACEHOLDER,
                    currentDirectory.substring(currentDirectory.lastIndexOf("/") + 1));
            cMakeTemplateString = cMakeTemplateString.replaceAll(USERNAME_PLACEHOLDER, currentUser);
            fileReader.close();

            File cMakeResult = new File(currentDirectory + "/CMakeLists.txt");
            if (!cMakeResult.createNewFile()) return 1;
            FileWriter fileWriter = new FileWriter(cMakeResult);
            fileWriter.write(cMakeTemplateString);
            fileWriter.close();

        } catch (IOException e) {
            return 1;
        }
        return 0;
    }

    private Integer editSourceCode() {

        return 0;
    }
}
