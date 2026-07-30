import turtle
import time

# --- Setup Screen ---
screen = turtle.Screen()
screen.title("Robot Turning & Degrees Demo")
screen.setup(600, 600)
screen.bgcolor("#ffffff")

# --- Create Turtle (The Robot) ---
robot = turtle.Turtle()
robot.shape("turtle")  # Classic turtle icon makes directional heading obvious
robot.color("darkgreen")
robot.pensize(2)
robot.speed(2)  # Moderate speed for clear visual demonstration

# --- Draw Outer Blue Boundary First ---
robot.penup()
robot.goto(0, -180)
robot.pendown()
robot.pencolor("royalblue")
robot.pensize(3)
robot.circle(180)

# --- Define Angles (0° at Top / North) ---
# In robot movement, 0° is straight ahead (North), turning clockwise
angles_and_labels = [
    (0, "0° / 360°"),
    (45, "45°"),
    (90, "90°"),
    (135, "135°"),
    (180, "180°"),
    (225, "225°"),
    (270, "270°"),
    (315, "315°")
]

# --- Demo Robot Turning & Drawing Spokes ---
for deg, label in angles_and_labels:
    # 1. Reset to center
    robot.penup()
    robot.goto(0, 0)
    
    # 2. Point straight UP (0° North) first
    robot.setheading(90)
    
    # 3. Rotate clockwise to target degree (90 - deg converts Standard Math to Compass/Robot Heading)
    robot.setheading(90 - deg)
    
    # Pause briefly so students see the heading turn!
    time.sleep(0.3)
    
    # 4. Move forward to draw the degree line
    robot.pendown()
    robot.pencolor("black")
    robot.pensize(1.5)
    robot.forward(180)
    
    # 5. Stamp label
    robot.penup()
    robot.forward(25)
    robot.pencolor("black")
    robot.write(label, align="center", font=("Arial", 11, "bold"))

# --- Mark Center Point ---
robot.goto(0, 0)
robot.color("red")
robot.stamp()  # Mark the pivot center

# Hide turtle arrow when done
robot.hideturtle()

turtle.done()
