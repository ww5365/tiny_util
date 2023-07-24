#include "third_party/LightGBM/application.h"
#include "third_party/LightGBM/c_api.h"
#include "third_party/LightGBM/config.h"
#include "third_party/LightGBM/boosting.h"
#include "third_party/LightGBM/utils/common.h"
#include "third_party/LightGBM/prediction_early_stop.h"


    LightGBM::Boosting* boosterV2;
    LightGBM::PredictionEarlyStopInstance early_stop_v2_;


        // load v2 model
        boosterV2 = LightGBM::Boosting::CreateBoosting("gbdt", nullptr);
        if (!LightGBM::Boosting::LoadFileToBoosting(boosterV2, "../config/web/gt_lp_model_v2.txt")) {
            COMLOG_INFO("load generic_timeliness_level_predict_model_file failed: gt_lp_model_v2.txt");
            return false;
        }
        boosterV2->InitPredict(0, -1, false);
        early_stop_v2_ = CreatePredictionEarlyStopInstance("none", LightGBM::PredictionEarlyStopConfig());

        // load v2 prob model
        boosterProbV2 = LightGBM::Boosting::CreateBoosting("gbdt", nullptr);
        if (!LightGBM::Boosting::LoadFileToBoosting(boosterProbV2, "../config/web/gt_prob_model_v2.txt")) {
            COMLOG_INFO("load generic_timeliness_prob_predict_model_file failed: gt_prob_model_v2.txt");
            return false;
        }
        boosterProbV2->InitPredict(0, -1, false);
        early_stop_prob_v2_ = CreatePredictionEarlyStopInstance("none", LightGBM::PredictionEarlyStopConfig());


    // get model predict level
    std::vector<double> out(5, 0);
    double* output = static_cast<double*>(out.data());
    std::vector<double> outProb(1, 0);
    double *outputProb = static_cast<double*>(outProb.data());

        boosterV2->Predict(input.data(), output, &early_stop_v2_);
        boosterProbV2->Predict(input.data(), outputProb, &early_stop_prob_v2_);





