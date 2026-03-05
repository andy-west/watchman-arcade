using System.Text;
using NAudio.Wave;
using NAudio.Wave.SampleProviders;

namespace SoundConverter;

internal class Program
{
    private const int TargetSampleRate = 16000;
    private const int ValuesPerLine = 25;

    private static void Main()
    {
        var soundsFolder = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "sounds");

        if (!Directory.Exists(soundsFolder))
        {
            Console.WriteLine($"Error: Sounds folder not found at {soundsFolder}");
            return;
        }

        var wavFiles = Directory.GetFiles(soundsFolder, "*.wav");

        if (wavFiles.Length == 0)
        {
            Console.WriteLine("No .wav files found in the sounds folder.");
            return;
        }

        foreach (var wavFile in wavFiles)
        {
            try
            {
                ConvertWavToCsv(wavFile);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error processing {Path.GetFileName(wavFile)}: {ex.Message}");
            }
        }
    }

    private static void ConvertWavToCsv(string wavFilePath)
    {
        var fileName = Path.GetFileNameWithoutExtension(wavFilePath);
        var outputPath = Path.Combine(Path.GetDirectoryName(wavFilePath)!, $"{fileName}.csv");

        Console.WriteLine($"Converting {Path.GetFileName(wavFilePath)}...");

        using var reader = new AudioFileReader(wavFilePath);

        // Resample to 16 kHz mono.
        var monoStream = reader.WaveFormat.Channels > 1
            ? new WaveFloatTo16Provider(new StereoToMonoSampleProvider(reader).ToWaveProvider())
            : new WaveFloatTo16Provider(reader.ToWaveProvider());

        var resampler = new MediaFoundationResampler(monoStream, new WaveFormat(TargetSampleRate, 16, 1));
        resampler.ResamplerQuality = 60;

        // Read all resampled 16-bit samples, then convert to unsigned 8-bit.
        using var memStream = new MemoryStream();
        var buffer = new byte[resampler.WaveFormat.AverageBytesPerSecond];
        int bytesRead;

        while ((bytesRead = resampler.Read(buffer, 0, buffer.Length)) > 0)
        {
            memStream.Write(buffer, 0, bytesRead);
        }

        resampler.Dispose();

        var rawBytes = memStream.ToArray();
        int sampleCount = rawBytes.Length / 2;
        var samples = new byte[sampleCount];

        for (int i = 0; i < sampleCount; i++)
        {
            var sample16 = BitConverter.ToInt16(rawBytes, i * 2);
            // Convert signed 16-bit to unsigned 8-bit: shift from [-32768, 32767] to [0, 255].
            samples[i] = (byte)((sample16 + 32768) >> 8);
        }

        // Write as CSV with ValuesPerLine values per line.
        var csv = new StringBuilder();

        for (int i = 0; i < samples.Length; i++)
        {
            csv.Append($"0x{samples[i]:X2}");

            if (i < samples.Length - 1)
            {
                csv.Append((i + 1) % ValuesPerLine == 0 ? ",\n" : ", ");
            }
        }

        csv.AppendLine();
        File.WriteAllText(outputPath, csv.ToString());

        Console.WriteLine($"  -> {Path.GetFileName(outputPath)} ({samples.Length} samples)");
    }
}
