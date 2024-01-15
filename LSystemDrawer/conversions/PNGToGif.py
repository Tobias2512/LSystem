from PIL import Image

def convert_png_to_gif(png_path, gif_path):
    try:
        # Open the PNG image
        png_image = Image.open(png_path)

        # Convert and save as GIF
        png_image.save(gif_path, format="GIF")

        print(f"Conversion successful. GIF saved to {gif_path}")
    except Exception as e:
        print(f"Error: {e}")

# Replace 'input.png' and 'output.gif' with your file paths

convert_png_to_gif("png/yellowbird-downflap.png", "flappybird/bird2.gif")
convert_png_to_gif("png/yellowbird-midflap.png", "flappybird/bird1.gif")
convert_png_to_gif("png/yellowbird-upflap.png", "flappybird/bird0.gif")
