import turtle
import time


def setup(title, bgcolor, sun):
    turtle.title(title)
    turtle.clear()
    screen = turtle.Screen()
    screen.bgcolor(bgcolor)
    height = turtle.window_height()
    width = turtle.window_width()
    turtle.hideturtle()
    turtle.tracer(0)
    turtle.delay(0)
    if sun:
        draw_sun(0, height/2)
        draw_bird(0, height/4)
        draw_bird(-300, height/2)
        draw_bird(300, height/2)
    return width, height


def draw_sun(x, y):
    t = turtle.Turtle()
    turtle.tracer(0)
    t.penup()
    t.goto(x, y)
    t.pendown()
    turtle.register_shape("gif/happysun.gif")
    t.begin_fill()
    t.shape("gif/happysun.gif")
    t.end_fill()


def draw_bird(x, y):
    t = turtle.Turtle()
    turtle.tracer(0)
    t.penup()
    t.goto(x, y)
    t.pendown()
    turtle.register_shape("gif/bird_upflap.gif")
    t.begin_fill()
    t.shape("gif/bird_upflap.gif")
    t.end_fill()


def drawAppleTree(filename, distance, angle, update, heading, position):  # update = after how many branches the screen updates (really improves speed if this is set high)
    updatecounter = 0
    applecounter = 0
    state_stack = []
    t = turtle.Turtle()
    t.hideturtle()
    t.speed(0)  # setup speed
    t.penup()  # we don't want to draw when turtle is going to initial position
    t.setheading(heading)  # we want to face the right direction
    t.goto(position)  # begin in the right place
    t.pendown()  # we can begin drawing
    t.pencolor("brown4")
    t.pensize(3)
    with open(filename, "r") as file:  # open file in read mode as f
        for line in file:
            for symbol in line:
                if symbol == 'F':  # if the symbol we read is in alphabet go forward by distance.
                    t.forward(distance)
                elif symbol == '+':  # if the symbol we read is '+' go right by angle
                    t.left(angle)
                elif symbol == '-':  # if the symbol we read is '-' go left by angle
                    t.right(angle)
                elif symbol == '[':  # if the symbol we read is '[' put state on stack
                    state_stack.append((t.position(), t.heading()))
                elif symbol == ']':  # if the symbol we read is ']' take save state from stack
                    if state_stack:  # if there is still a state in stack (which it should otherwise fault with implementation)
                        savedPosition, savedHeading = state_stack.pop()  # restore state
                        t.penup()
                        t.goto(savedPosition)
                        t.setheading(savedHeading)
                        t.pendown()
                        if (updatecounter <= update):  # after every 100 branches update the screen so it gets a nice evolution
                            updatecounter += 1
                        else:
                            updatecounter = 0
                            turtle.update()
                            turtle.tracer(0)
                            turtle.hideturtle()
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


def drawEvolutionTree(filename, distance, angle):
    applecounter = 0
    repeat = 0
    state_stack = []
    width, height = setup("Draw Evolution Of A Plant", "light goldenrod yellow", sun=False)
    t = turtle.Turtle()
    t.speed(0)  # setup speed
    t.penup()  # we don't want to draw when turtle is going to initial position
    t.setheading(90)  # we want to face North
    t.goto(0, -height + 300)
    t.pendown()  # we can begin drawing
    t.pencolor("brown4")
    t.pensize(3)
    while repeat <= 5:
        with open(filename, "r") as file:  # open file in read mode as f
            for line in file:
                previous_time = time.time()  # Save the current time before drawing
                t.penup()
                t.goto(0, -height + 300)
                t.setheading(90)
                turtle.hideturtle()
                turtle.update()  # update the screen after every tree
                t.clear()  # clear when turtle is already removed so the previous tree gets cleared and the next tree comes on our screen when turtle.update() gets called
                t.pendown()
                for symbol in line:
                    if symbol == 'F':  # if the symbol we read is in alphabet go forward by distance.
                        t.forward(distance)
                    elif symbol == '+':  # if the symbol we read is '+' go right by angle
                        t.left(angle)
                    elif symbol == '-':  # if the symbol we read is '-' go left by angle
                        t.right(angle)
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
                                t.fillcolor("green3")  # or an apple after every 50 branches
                                applecounter += 1
                            else:
                                applecounter = 0
                                t.pencolor("red")
                                t.fillcolor("red")
                            t.begin_fill()
                            t.circle(3)
                            t.end_fill()
                            t.pencolor("brown4")
                # I want every stage of the tree to be shown 5 seconds.
                elapsed_time = time.time() - previous_time  # save the difference between current time and the time before drawing
                while elapsed_time <= 5:  # If this is bigger then 5sec we go to the next tree
                    elapsed_time = time.time() - previous_time
        turtle.update()
        turtle.hideturtle()
        repeat += 1
    turtle.done()


def drawCollageTrees(filename1, filename2, filename3, distance, angle1, angle2, update):
    # The colors i use are from this site: https://cs111.wellesley.edu/labs/lab02/colors
    offset = 200
    width, height = setup("Drawing Beautiful Screen", "skyblue", sun=True)
    drawAppleTree(filename2, distance, angle2, update, 90, (0, -height + offset))  # facing north, down right corner (little more left)
    drawAppleTree(filename2, distance, angle2, update, 90, (width/3, -height + offset))  # facing north, down right corner (little more left)
    drawAppleTree(filename2, distance, angle2, update, 90, (-width/3, -height + offset))  # facing north, down little left
    drawAppleTree(filename1, distance, angle1, update, 0, (-width, height/3))  # facing east, upper left corner(little lower)
    drawAppleTree(filename1, distance, angle1, update, 0, (-width, 0))  # facing east, middle left corner
    drawAppleTree(filename3, distance, angle1, update, 180, (width, height/3))  # facing west, upper right corner
    drawAppleTree(filename3, distance, angle1, update, 180, (width, 0))  # facing west, middle right corner
    turtle.done()


if __name__ == "__main__":
    #drawCollageTrees("txt/lsystem_output1.txt", "txt/lsystem_output2.txt", "txt/lsystem_output3.txt", 2, 25, 25.7, 10000)
    drawEvolutionTree("txt/lsystem_evolutionplant.txt", 2, 25.7)