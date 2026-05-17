// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
#pragma once
#include<fstream>
#include<string>

class ExperimentLogger{
  public:
    ExperimentLogger(const std::string& path);

    void logSaResult(
        double start_temp,
        double end_temp,
        int best_score,
        double elapsed,
        int operation_count,
        int snake_size,
        int seed
    );

    void logBeamResult(
        int beam_width,
        int best_score
    );


  private:
    enum class Format{
      SimulatedAnnealing,
      BeamSearch
    };

    std::ofstream ofs_;
    Format format_;
};
