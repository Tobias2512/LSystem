import turtle
import os


def drawAppleTree(filename, heading, position):  # update = after how many branches the screen updates (really improves speed if this is set high)
    t = turtle.Turtle()
    applecounter = 0
    state_stack = []
    t.hideturtle()
    t.speed(0)  # setup speed
    t.penup()  # we don't want to draw when turtle is going to initial position
    t.setheading(heading)  # we want to face the right direction
    t.goto(position)  # begin in the right place
    t.pendown()  # we can begin drawing
    t.pencolor("brown4")
    t.pensize(5)
    turtle.delay(0)
    turtle.tracer(0)
    with open(filename, "r") as file:  # open file in read mode as f
        line = file.readline()
        for symbol in line:
                if symbol == 'F':  # if the symbol we read is in alphabet go forward by distance.
                    t.forward(2)
                elif symbol == '+':  # if the symbol we read is '+' go right by angle
                    t.left(25.7)
                elif symbol == '-':  # if the symbol we read is '-' go left by angle
                    t.right(25.7)
                elif symbol == '[':  # if the symbol we read is '[' put state on stack
                    state_stack.append((t.position(), t.heading()))
                elif symbol == ']':  # if the symbol we read is ']' take save state from stack
                    if state_stack:  # if there is still a state in stack (which it should otherwise fault with implementation)
                        savedPosition, savedHeading = state_stack.pop()  # restore state
                        t.penup()
                        t.goto(savedPosition)
                        t.setheading(savedHeading)
                        t.pendown()
                        if applecounter < 50:
                            t.pencolor("green3")  # draw a leaf after every ending branch
                            t.fillcolor("green3") # or an apple after every 50 branches
                            applecounter += 1
                        else:
                            applecounter = 0
                            t.pencolor("red")
                            t.fillcolor("red")
                        t.begin_fill()
                        t.circle(3)
                        t.end_fill()
                        t.pencolor("brown4")
    turtle.update()
    turtle.hideturtle()


def save_turtle_drawing_as_gif(gif_path, heading, position):
    # Set up the turtle
    turtle.bgcolor("white")
    turtle.title("Turtle Tree")

    # Draw the turtle graphics onto the image
    drawAppleTree("txt/lsystem_output2.txt", heading, position)

    canvas = turtle.getcanvas()

    # Capture the turtle graphics as PostScript data
    ps_data = canvas.postscript(colormode='color')

    # Save the PostScript data to an EPS file
    eps_filename = "temp.eps"
    with open(eps_filename, "w", encoding="utf-8") as eps_file:
        eps_file.write(ps_data)

    # Add Ghostscript to PATH
    ghostscript_path = r"C:\Users\hagen\Documents\gs10.02.1\bin\gswin64c.exe"
    os.environ['PATH'] += os.pathsep + ghostscript_path

    convert_command = r'"C:\Program Files\ImageMagick-7.1.1-Q16-HDRI\magick.exe"'

    # Convert the EPS file to a GIF using PIL
    os.system(f'{convert_command} -delay 10 -loop 0 {eps_filename} {gif_path}')

    # Remove the temporary EPS file
    os.remove(eps_filename)

    print(f"Drawing saved as GIF: {gif_path}")

def mainBottom():

    width = turtle.window_width()
    height = turtle.window_height()

    # Save the turtle drawing as a GIF file
    save_turtle_drawing_as_gif("flappybird/lsystem_tree_bottom.gif", 90, (0, -height/2))

    # Close the turtle graphics window when clicked
    turtle.exitonclick()


def mainTop():

    width = turtle.window_width()
    height = turtle.window_height()

    # Save the turtle drawing as a GIF file
    save_turtle_drawing_as_gif("flappybird/lsystem_tree_top.gif", 270, (0, height/2))

    # Close the turtle graphics window when clicked
    turtle.exitonclick()



if __name__ == "__main__":
    mainTop()
