// Copyright Owl Creek Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LedgerLog.h"
#include "LedgerValue.generated.h"

/**
 * @brief Enumeration representing the type of state values.
 *
 * This enum is used to identify the type of a state value at runtime.
 */
UENUM(BlueprintType)
enum class ELedgerValueType : uint8
{
	Null    UMETA(DisplayName = "None"),
	Int32	UMETA(DisplayName = "Integer"),
	Float   UMETA(DisplayName = "Float"),
	Bool    UMETA(DisplayName = "Boolean"),
	String  UMETA(DisplayName = "String")
};

template<typename> struct TLedgerValueType {};
template<> struct TLedgerValueType<int32>  { static constexpr ELedgerValueType Value = ELedgerValueType::Int32; };
template<> struct TLedgerValueType<float>  { static constexpr ELedgerValueType Value = ELedgerValueType::Float; };
template<> struct TLedgerValueType<bool>   { static constexpr ELedgerValueType Value = ELedgerValueType::Bool; };
template<> struct TLedgerValueType<FString>{ static constexpr ELedgerValueType Value = ELedgerValueType::String; };

using FCreekStateVariantType = TVariant<int32, float, bool, FString>;

// A lightweight, variant-like value holder for use in ULedger domains
USTRUCT(Blueprintable)
struct FLedgerValue
{
	GENERATED_BODY()
	
public:
	FLedgerValue()
	{
		Value.Set<int32>(0);
		Type = ELedgerValueType::Null;
	}

	explicit FLedgerValue(const int32 InValue)
	{
		Set(InValue);
	}
	
	explicit FLedgerValue(const float InValue)
	{
		Set(InValue);
	}
	
	explicit FLedgerValue(const bool InValue)
	{
		Set(InValue);
	}
	
	explicit FLedgerValue(const FString& InValue)
	{
		Set(InValue);
	}
	
	ELedgerValueType GetType() const
	{
		return Type;
	}
	
	void Set(const int32 InValue)
	{
		Value.Set<int32>(InValue);
		Type = ELedgerValueType::Int32;
	}
	
	void Set(const float InValue)
	{
		Value.Set<float>(InValue);
		Type = ELedgerValueType::Float;
	}
	
	void Set(const bool InValue)
	{
		Value.Set<bool>(InValue);
		Type = ELedgerValueType::Bool;
	}
	
	void Set(const FString& InValue)
	{
		Value.Set<FString>(InValue);
		Type = ELedgerValueType::String;
	}
	
	template<typename T>
	bool TryGet(T& OutValue) const
	{
		constexpr ELedgerValueType ExpectedType = TLedgerValueType<T>::Value;

		if (Type != ExpectedType)
		{
			UE_LOG(LogLedger, Warning, TEXT("Type mismatch in TryGet: Expected %s, but current type is %s."),
				*UEnum::GetValueAsString(ExpectedType),
				*UEnum::GetValueAsString(Type));
			
			return false;
		}

		if (const T* Ptr = Value.TryGet<T>())
		{
			OutValue = *Ptr;
			return true;
		}
		
		UE_LOG(LogLedger, Error, TEXT("TryGet failed unexpectedly despite matching type."));
		return false;
	}
	
	FString ToString() const
	{
		return Match(
			[](const int32 V) { return FString::Printf(TEXT("%d"), V); },
			[](const float V) { return FString::SanitizeFloat(V); },
			[](const bool V) { return V ? FString(TEXT("true")) : FString(TEXT("false")); },
			[](const FString& V) { return V; },
			[]() { return FString(TEXT("None")); }
		);
	}

	template<typename FInt, typename FFloat, typename FBool, typename FStringF, typename FNull>
	auto Match(FInt IntFn, FFloat FloatFn, FBool BoolFn, FStringF StringFn, FNull NullFn) const
	{
		switch (Type)
		{
			case ELedgerValueType::Int32:
				return IntFn(Value.Get<int32>());
			case ELedgerValueType::Float:
				return FloatFn(Value.Get<float>());
			case ELedgerValueType::Bool:
				return BoolFn(Value.Get<bool>());
			case ELedgerValueType::String:
				return StringFn(Value.Get<FString>());
			case ELedgerValueType::Null:
				return NullFn();
			default:
				checkf(false, TEXT("FATAL: Unsupported type in FLedgerValue::Match!"));
				return NullFn();
		}
	}

private:
	UPROPERTY(BlueprintReadOnly, Category = "Ledger", meta = (AllowPrivateAccess = "true"))
	ELedgerValueType Type = ELedgerValueType::Null;
	
	FCreekStateVariantType Value;
};
