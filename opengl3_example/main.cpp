// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include  <cctype>
#include <string>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void toLowerCaseSTD(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
}

class c_players
{
public:
	int score_west_coast;
	int score_east_coast ;
	int score_north ;
	int score_south ;
	int score_mid_west ;
	int total_score ;
	int correct_answers;
	int incorrect_answers;

	c_players()
	{
		score_west_coast = 0;
		score_east_coast = 0;
		score_north = 0;
		score_south = 0;
		score_mid_west = 0;
		total_score = 0;
		correct_answers = 0;
		incorrect_answers = 0;
	}
};

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    gl3wInit();

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'extra_fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		//yyvytvytvuyfvghuj
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

		static int current_selected = -1;
		int correct = 0, incorrect = 0;
		char buffer[15];
		int players;
		static bool main_open = true;
		static bool once = false;
		std::vector<int> arrayplayers = {};
		std::vector<c_players> amount_of_players;
		int players_2 = 0;
		char answer1[10];
		char answer2[10];

		char question3[20];
		char question4[20];

		ImGui::Begin("Questions Game", &main_open, ImVec2{510, 50});
		{
			ImGui::InputInt("Number of Players", &players);

			if (!once)
			{
				players = 0;
				once = true;
			}

			if (players <= 0)
				players = 1;

			if (ImGui::Button("East Coast", ImVec2(100, 20)))
				current_selected = 0;
			ImGui::SameLine();
			if (ImGui::Button("West Coast", ImVec2(100, 20)))
				current_selected = 1;
			ImGui::SameLine();
			if (ImGui::Button("North", ImVec2(100, 20)))
				current_selected = 2;
			ImGui::SameLine();
			if (ImGui::Button("South", ImVec2(100, 20)))
				current_selected = 3;
			ImGui::SameLine();
			if (ImGui::Button("Midwest", ImVec2(100, 20)))
				current_selected = 4;

			/*if (check1)
			{
				ImGui::InputText("Which state is the Statue of Liberty located in?", buffer, sizeof(buffer));
			}

			/*ImGui::InputText("Which country is the United States south of?", buffer, sizeof(buffer));

			int check = 0;

			for (size_t c = 0; c <= sizeof(buffer); c++)
			{
				std::string str = "Canada";

				if (buffer[c] == str[c])
					check++;
			}

			if (check == 7)
				ImGui::Text("Correct");
			else
				ImGui::Text("Incorrect");		*/	
			players_2 = players;

			for (int i = 0; i < players_2;)
			{
				c_players* player = new c_players();
				amount_of_players.push_back(*player);
				players_2--;
			}

			
			ImGui::Text("players in object = %i", (int)amount_of_players.size());
			ImGui::Text("Players = %i", players);
			
			
		}

		static bool open = true;

		ImGui::End();

		switch (current_selected)
		{
		case 0:
		{
			ImGui::Begin("East Coast", &open, ImVec2{400, 400});
			

			ImGui::InputText("What city is the Statue of Liberty located in?", answer1, sizeof(answer1));
			ImGui::InputText("What is the city that has central park?", answer2, sizeof(answer2));

			for (auto c = 0; c <= 2; c++)
			{
			}

		

			ImGui::End();

			break;
		}
		case 1:
		{
			ImGui::Begin("West Coast", &open, ImVec2{ 400, 400 });

			ImGui::End();
			break;
		}
		case 2:
		{
			ImGui::Begin("North", &open, ImVec2{ 400, 400 });
			ImGui::End();
			break;
		}
		case 3:
		{
			ImGui::Begin("South", &open, ImVec2{ 400, 400 });
			ImGui::End();
			break;
		}
		case 4:
		{
			ImGui::Begin("Mid West", &open, ImVec2{ 400, 400 });
			ImGui::End();
			break;
		}
		default:
			break;
		}

	
		
        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}
