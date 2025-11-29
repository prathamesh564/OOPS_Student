"use client";
import { useState } from "react";
import Header from "../components/Header";
import Footer from "../components/Footer";

export default function Student() {
  const [roll, setRoll] = useState("");
  const [data, setData] = useState(null);

  const fetchStudent = async () => {
    const res = await fetch(`http://localhost:5000/student/${roll}`);
    if (!res.ok) {
      setData("notfound");
      return;
    }
    const json = await res.json();
    setData(json);
  };

  return (
    <div>
      <Header />

      <div className="max-w-lg mx-auto bg-white shadow p-6 mt-8 rounded">
        <h2 className="text-xl font-bold mb-4">Enter Roll Number</h2>

        <input
          className="border p-2 w-full mb-4"
          placeholder="Enter Roll Number"
          onChange={(e) => setRoll(e.target.value)}
        />

        <button
          className="bg-blue-600 text-white px-4 py-2 rounded w-full"
          onClick={fetchStudent}
        >
          Search
        </button>

        <div className="mt-6">
          {data === "notfound" && (
            <p className="text-red-500 font-bold text-center">Student Not Found</p>
          )}

          {data && data !== "notfound" && (
            <div className="p-4 border rounded bg-gray-50">
              <p><strong>Name:</strong> {data.name}</p>
              <p><strong>USN:</strong> {data.usn}</p>
              <p><strong>Section:</strong> {data.section}</p>
              <p><strong>Department:</strong> {data.department}</p>
              <p><strong>Contact:</strong> {data.contact}</p>
            </div>
          )}
        </div>
      </div>

      <Footer />
    </div>
  );
}
