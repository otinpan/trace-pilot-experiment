// @trace-pilot c041b61f1898609dde303ca4926e67b605ec94da
#include"experiment_logger.h"
#include<filesystem>

ExperimentLogger::ExperimentLogger(const std::string& path){
  const std::string stem=std::filesystem::path(path).stem().string();
  format_=(stem=="beam_experiment")
    ? Format::BeamSearch
    : Format::SimulatedAnnealing;

  const bool exists=std::filesystem::exists(path);
  const bool has_content=
    exists && std::filesystem::is_regular_file(path) &&
    std::filesystem::file_size(path)>0;

  ofs_.open(path,std::ios::app);

  if(!has_content){
    if(format_==Format::BeamSearch){
      ofs_<<"beam_width,best_score\n";
    }else{
      ofs_<<"start_temp,end_temp,best_score,elapsed,operation_count,snake_size,seed\n";
    }
  }
}

void ExperimentLogger::logSaResult(
    double start_temp,
    double end_temp,
    int best_score,
    double elapsed,
    int operation_count,
    int snake_size,
    int seed
){
  ofs_
    <<start_temp<<","
    <<end_temp<<","
    <<best_score<<","
    <<elapsed<<","
    <<operation_count<<","
    <<snake_size<<","
    <<seed<<"\n";
}

void ExperimentLogger::logBeamResult(
    int beam_width,
    int best_score
){
  ofs_
    <<beam_width<<","
    <<best_score<<"\n";
}
