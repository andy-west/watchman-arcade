using System.Drawing;
using System.Text;

#pragma warning disable CA1416

namespace ImageConverter
{
    internal class Program
    {
        private static void Main()
        {
            Console.WriteLine("Loading title_screen.png and analyzing colors...");

            try
            {
                // Path to the image file
                var imagePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "title_screen.png");
                var outputPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "title_screen.cpp");

                if (!File.Exists(imagePath))
                {
                    Console.WriteLine($"Error: File not found at {imagePath}");
                    return;
                }

                // Load the image
                using var bitmap = new Bitmap(imagePath);

                // Dictionary to store unique colors
                var colorCounts = new Dictionary<Color, int>();

                // Scan each pixel in the image
                for (int y = 0; y < bitmap.Height; y++)
                {
                    for (int x = 0; x < bitmap.Width; x++)
                    {
                        var pixelColor = bitmap.GetPixel(x, y);

                        if (!colorCounts.TryAdd(pixelColor, 1))
                        {
                            colorCounts[pixelColor]++;
                        }
                    }
                }

                // Output the results
                Console.WriteLine($"Image dimensions: {bitmap.Width}x{bitmap.Height}");
                Console.WriteLine($"Found {colorCounts.Count} distinct colors:");

                int colorIndex = 1;

                foreach (var colorEntry in colorCounts)
                {
                    var color = colorEntry.Key;
                    Console.WriteLine($"Color {colorIndex}: RGB({color.R}, {color.G}, {color.B}), Alpha: {color.A}, Count: {colorEntry.Value} pixels");
                    colorIndex++;
                }

                // Map colors to values: 1 (black), 2 (gray), 3 (white)
                var colorMapping = new Dictionary<Color, byte>();

                // Map colors based on brightness (luminance)
                foreach (var color in colorCounts.Keys)
                {
                    // Calculate luminance (perceived brightness)
                    var luminance = 0.299 * color.R + 0.587 * color.G + 0.114 * color.B;

                    colorMapping[color] = luminance switch
                    {
                        // Dark (0-85)
                        < 85 => 1,
                        // Medium (85-170)
                        < 170 => 2,
                        _ => 3
                    };
                }

                Console.WriteLine("\nColor mapping:");

                foreach (var (color, value) in colorMapping)
                {
                    var colorName = value switch
                    {
                        1 => "Black",
                        2 => "Gray",
                        _ => "White"
                    };

                    Console.WriteLine($"RGB({color.R}, {color.G}, {color.B}) -> {value} ({colorName})");
                }

                // Generate the CPP file content
                var cppContent = new StringBuilder();
                cppContent.AppendLine("#include <arduino.h>");
                cppContent.AppendLine();
                cppContent.AppendLine("byte screen_data[] = {");

                // Add width and height
                //cppContent.AppendLine($"  {bitmap.Width}, {bitmap.Height},");

                // Add pixel data
                for (int y = 0; y < bitmap.Height; y++)
                {
                    cppContent.Append("  ");

                    for (int x = 0; x < bitmap.Width; x++)
                    {
                        var pixelColor = bitmap.GetPixel(x, y);
                        var colorValue = colorMapping[pixelColor];

                        cppContent.Append(colorValue);

                        // Add comma if not the last pixel of the last row
                        if (x < bitmap.Width - 1 || y < bitmap.Height - 1)
                            cppContent.Append(", ");
                    }
                    cppContent.AppendLine();
                }

                cppContent.AppendLine("};");

                // Write to file
                File.WriteAllText(outputPath, cppContent.ToString());
                Console.WriteLine($"\nSuccessfully wrote image data to {outputPath}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error processing image: {ex.Message}");
            }

            Console.WriteLine("\nPress any key to exit...");
            Console.ReadKey();
        }
    }
}
