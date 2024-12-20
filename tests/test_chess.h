//
// Created by Ismael Cuevas on 11/2/24.
//

#ifndef CHESS_TEST_CHESS_H
#define CHESS_TEST_CHESS_H

#include <gtest/gtest.h>
#include "ApprovalTests.hpp"
#include <filesystem>
#include <fstream>
#include "../headers/ChessPieces/King.h"
#include "../headers/ChessPieces/Bishop.h"
#include "../headers/ChessPieces/Rook.h"
#include "../headers/ChessPieces/Pawn.h"
#include "../headers/ChessPieces/Knight.h"
#include "../headers/ChessMediator/ChessMediator.h"
#include "../headers/ChessBoard/ChessBoardModel.h"
#include "../enum/PieceType.h"
#include "../headers/Utils/StringUtils.h"

class WindowsCompatibleNamer : public ApprovalTests::ApprovalNamer {
public:
    WindowsCompatibleNamer(const std::string& testName) : testName_(testName) {
        basePath_ = std::filesystem::current_path() / "approval_tests";
        basePath_.make_preferred();
    }

    std::string getApprovedFile(std::string extension) const override {
        auto path = basePath_ / (testName_ + ".approved" + extension);
        return path.make_preferred().string();
    }

    std::string getReceivedFile(std::string extension) const override {
        auto path = basePath_ / (testName_ + ".received" + extension);
        return path.make_preferred().string();
    }

private:
    std::string testName_;
    std::filesystem::path basePath_;
};

class WindowsApprovalTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDir_ = std::filesystem::current_path() / "approval_tests";
        testDir_.make_preferred();

        if (!std::filesystem::exists(testDir_)) {
            std::filesystem::create_directories(testDir_);
        }

        ApprovalTests::Approvals::useApprovalsSubdirectory(testDir_.string());
    }

    void ensureApprovalFiles(const std::string& testName, const std::string& content) {
        try {
            WindowsCompatibleNamer namer(testName);
            auto approvedPath = std::filesystem::path(namer.getApprovedFile(".txt"));
            auto receivedPath = std::filesystem::path(namer.getReceivedFile(".txt"));

            // Add a newline to the content to ensure consistency
            std::string contentWithNewline = content + "\n";

            auto writeExactContent = [](const std::filesystem::path& path, const std::string& data) {
                std::ofstream file(path, std::ios::binary);
                if (!file) {
                    throw std::runtime_error("Failed to create file: " + path.string());
                }
                file.write(data.c_str(), data.length());
            };

            if (!std::filesystem::exists(approvedPath)) {
                std::cout << "Creating approved file at: " << approvedPath << std::endl;
                writeExactContent(approvedPath, contentWithNewline);
            }

            if (!std::filesystem::exists(receivedPath)) {
                std::cout << "Creating received file at: " << receivedPath << std::endl;
                writeExactContent(receivedPath, contentWithNewline);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error ensuring approval files: " << e.what() << std::endl;
            throw;
        }
    }

    void verifyWithWindowsCompatibility(const std::string& content, const std::string& testName) {
        auto namer = std::make_shared<WindowsCompatibleNamer>(testName);
        ensureApprovalFiles(testName, content);
        ApprovalTests::Approvals::verify(
            content,
            ApprovalTests::Options().withNamer(namer)
        );
    }

private:
    std::filesystem::path testDir_;
};

#endif //CHESS_TEST_CHESS_H
