#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h" // Map container
#include "TimeSeriesContainer.generated.h"

USTRUCT(BlueprintType)
struct FTimeSeriesData // struct for time series data
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Time;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;
};

UCLASS(Blueprintable)
class PROJECT_API UTimeSeriesContainer : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<float, float> TimeSeriesData; // Map to store time series data

    UFUNCTION(BlueprintCallable, Category = "Time Series")
    void AddDataPoint(float Time, float Value) // Function to add a data point to the map
    {
        if (TimeSeriesData.Contains(Time)) // The time already exists
        {
            UE_LOG(LogTemp, Error, TEXT("The time series data contains time already..."));
        }
        else
        {
            TimeSeriesData.Add(Time, Value);
        }
    }

    UFUNCTION(BlueprintCallable, Category = "Time Series")
    float GetValueAtTime(float Time) // Function to get the value at a specific time
    {
        float* ValuePtr = TimeSeriesData.Find(Time);
        if (ValuePtr)
        {
            return *ValuePtr;
        }

        // If time not found, implement interpolation or handle the error
        UE_LOG(LogTemp, Error, TEXT("Time not found in the time series data"));
        // If interpolation is required, you can use: return InterpolateValueAtTime(Time);
        return 0.0f; // Default value
    }

    UFUNCTION(BlueprintCallable, Category = "Time Series")
    TArray<FTimeSeriesData> GetAllDataPoints() const // Function to get all data points as an array
    {
        TArray<FTimeSeriesData> DataPoints;
        for (const auto& Entry : TimeSeriesData)
        {
            FTimeSeriesData DataPoint;
            DataPoint.Time = Entry.Key;
            DataPoint.Value = Entry.Value;
            DataPoints.Add(DataPoint);
        }
        return DataPoints;
    }

    UFUNCTION(BlueprintCallable, Category = "Time Series")
    void ClearData() // Function to clear all data
    {
        TimeSeriesData.Empty();
    }
};